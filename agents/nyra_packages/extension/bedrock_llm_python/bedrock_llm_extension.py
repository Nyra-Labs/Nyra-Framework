from .bedrock_llm import BedrockLLM, BedrockLLMConfig
from datetime import datetime
from threading import Thread
from ten import (
    Addon,
    Extension,
    register_addon_as_extension,
    TenEnv,
    Cmd,
    Data,
    StatusCode,
    CmdResult,
)


CMD_IN_FLUSH = "flush"
CMD_OUT_FLUSH = "flush"
DATA_IN_TEXT_DATA_PROPERTY_TEXT = "text"
DATA_IN_TEXT_DATA_PROPERTY_IS_FINAL = "is_final"
DATA_OUT_TEXT_DATA_PROPERTY_TEXT = "text"
DATA_OUT_TEXT_DATA_PROPERTY_TEXT_END_OF_SEGMENT = "end_of_segment"

PROPERTY_REGION = "region"  # Optional
PROPERTY_ACCESS_KEY = "access_key"  # Optional
PROPERTY_SECRET_KEY = "secret_key"  # Optional
PROPERTY_MODEL = "model"  # Optional
PROPERTY_PROMPT = "prompt"  # Optional
PROPERTY_TEMPERATURE = "temperature"  # Optional
PROPERTY_TOP_P = "top_p"  # Optional
PROPERTY_MAX_TOKENS = "max_tokens"  # Optional
PROPERTY_GREETING = "greeting"  # Optional
PROPERTY_MAX_MEMORY_LENGTH = "max_memory_length"  # Optional


def get_current_time():
    # Get the current time
    start_time = datetime.now()
    # Get the number of microseconds since the Unix epoch
    unix_microseconds = int(start_time.timestamp() * 1_000_000)
    return unix_microseconds


def is_punctuation(char):
    if char in [",", "，", ".", "。", "?", "？", "!", "！"]:
        return True
    return False


def parse_sentence(sentence, content):
    remain = ""
    found_punc = False

    for char in content:
        if not found_punc:
            sentence += char
        else:
            remain += char

        if not found_punc and is_punctuation(char):
            found_punc = True

    return sentence, remain, found_punc


class BedrockLLMExtension(Extension):
    memory = []
    max_memory_length = 10
    outdate_ts = 0
    bedrock_llm = None

    def on_start(self, nyra_env: TenEnv) -> None:
        nyra_env.log_info("BedrockLLMExtension on_start")
        # Prepare configuration
        bedrock_llm_config = BedrockLLMConfig.default_config()

        for optional_str_param in [
            PROPERTY_REGION,
            PROPERTY_ACCESS_KEY,
            PROPERTY_SECRET_KEY,
            PROPERTY_MODEL,
            PROPERTY_PROMPT,
        ]:
            try:
                value = nyra_env.get_property_string(optional_str_param).strip()
                if value:
                    bedrock_llm_config.__setattr__(optional_str_param, value)
            except Exception as err:
                nyra_env.log_debug(
                    f"GetProperty optional {optional_str_param} failed, err: {err}. Using default value: {bedrock_llm_config.__getattribute__(optional_str_param)}"
                )

        for optional_float_param in [PROPERTY_TEMPERATURE, PROPERTY_TOP_P]:
            try:
                value = nyra_env.get_property_float(optional_float_param)
                if value:
                    bedrock_llm_config.__setattr__(optional_float_param, value)
            except Exception as err:
                nyra_env.log_debug(
                    f"GetProperty optional {optional_float_param} failed, err: {err}. Using default value: {bedrock_llm_config.__getattribute__(optional_float_param)}"
                )

        try:
            max_tokens = nyra_env.get_property_int(PROPERTY_MAX_TOKENS)
            if max_tokens > 0:
                bedrock_llm_config.max_tokens = int(max_tokens)
        except Exception as err:
            nyra_env.log_debug(
                f"GetProperty optional {PROPERTY_MAX_TOKENS} failed, err: {err}. Using default value: {bedrock_llm_config.max_tokens}"
            )

        try:
            greeting = nyra_env.get_property_string(PROPERTY_GREETING)
        except Exception as err:
            nyra_env.log_debug(
                f"GetProperty optional {PROPERTY_GREETING} failed, err: {err}."
            )

        try:
            prop_max_memory_length = nyra_env.get_property_int(
                PROPERTY_MAX_MEMORY_LENGTH
            )
            if prop_max_memory_length > 0:
                self.max_memory_length = int(prop_max_memory_length)
        except Exception as err:
            nyra_env.log_debug(
                f"GetProperty optional {PROPERTY_MAX_MEMORY_LENGTH} failed, err: {err}."
            )

        # Create bedrockLLM instance
        try:
            self.bedrock_llm = BedrockLLM(bedrock_llm_config, nyra_env)
            nyra_env.log_info(
                f"newBedrockLLM succeed with max_tokens: {bedrock_llm_config.max_tokens}, model: {bedrock_llm_config.model}"
            )
        except Exception as err:
            nyra_env.log_error(f"newBedrockLLM failed, err: {err}")

        # Send greeting if available
        if greeting:
            try:
                output_data = Data.create("text_data")
                output_data.set_property_string(
                    DATA_OUT_TEXT_DATA_PROPERTY_TEXT, greeting
                )
                output_data.set_property_bool(
                    DATA_OUT_TEXT_DATA_PROPERTY_TEXT_END_OF_SEGMENT, True
                )
                nyra_env.send_data(output_data)
                nyra_env.log_info(f"greeting [{greeting}] sent")
            except Exception as err:
                nyra_env.log_info(f"greeting [{greeting}] send failed, err: {err}")
        nyra_env.on_start_done()

    def on_stop(self, nyra_env: TenEnv) -> None:
        nyra_env.log_info("BedrockLLMExtension on_stop")
        nyra_env.on_stop_done()

    def on_cmd(self, nyra_env: TenEnv, cmd: Cmd) -> None:
        nyra_env.log_info("BedrockLLMExtension on_cmd")
        cmd_json = cmd.to_json()
        nyra_env.log_info(f"BedrockLLMExtension on_cmd json: {cmd_json}")

        cmd_name = cmd.get_name()

        if cmd_name == CMD_IN_FLUSH:
            self.outdate_ts = get_current_time()
            cmd_out = Cmd.create(CMD_OUT_FLUSH)
            nyra_env.send_cmd(cmd_out, None)
            nyra_env.log_info("BedrockLLMExtension on_cmd sent flush")
        else:
            nyra_env.log_info(f"BedrockLLMExtension on_cmd unknown cmd: {cmd_name}")
            cmd_result = CmdResult.create(StatusCode.ERROR)
            cmd_result.set_property_string("detail", "unknown cmd")
            nyra_env.return_result(cmd_result, cmd)
            return

        cmd_result = CmdResult.create(StatusCode.OK)
        cmd_result.set_property_string("detail", "success")
        nyra_env.return_result(cmd_result, cmd)

    def on_data(self, nyra_env: TenEnv, data: Data) -> None:
        """
        on_data receives data from ten graph.
        current suppotend data:
          - name: text_data
            example:
            {name: text_data, properties: {text: "hello"}
        """
        nyra_env.log_info("BedrockLLMExtension on_data")

        # Assume 'data' is an object from which we can get properties
        try:
            is_final = data.get_property_bool(DATA_IN_TEXT_DATA_PROPERTY_IS_FINAL)
            if not is_final:
                nyra_env.log_info("ignore non-final input")
                return
        except Exception as err:
            nyra_env.log_info(
                f"OnData GetProperty {DATA_IN_TEXT_DATA_PROPERTY_IS_FINAL} failed, err: {err}"
            )
            return

        # Get input text
        try:
            input_text = data.get_property_string(DATA_IN_TEXT_DATA_PROPERTY_TEXT)
            if not input_text:
                nyra_env.log_info("ignore empty text")
                return
            nyra_env.log_info(f"OnData input text: [{input_text}]")
        except Exception as err:
            nyra_env.log_info(
                f"OnData GetProperty {DATA_IN_TEXT_DATA_PROPERTY_TEXT} failed, err: {err}"
            )
            return

        # Prepare memory. A conversation must alternate between user and assistant roles
        while len(self.memory):
            if len(self.memory) > self.max_memory_length:
                nyra_env.log_debug(
                    f"pop out first message, reason: memory length limit: `{self.memory[0]}`"
                )
                self.memory.pop(0)
            elif self.memory[0]["role"] == "assistant":
                nyra_env.log_debug(
                    f"pop out first message, reason: messages can not start with assistant: `{self.memory[0]}`"
                )
                self.memory.pop(0)
            else:
                break

        if len(self.memory) and self.memory[-1]["role"] == "user":
            # if last user input got empty response, append current user input.
            nyra_env.log_debug(
                "found last message with role `user`, will append this input into last user input"
            )
            self.memory[-1]["content"].append({"text": input_text})
        else:
            self.memory.append({"role": "user", "content": [{"text": input_text}]})

        def converse_stream_worker(start_time, input_text, memory):
            try:
                nyra_env.log_info(
                    f"GetConverseStream for input text: [{input_text}] memory: {memory}"
                )

                # Get result from Bedrock
                resp = self.bedrock_llm.get_converse_stream(memory)
                if resp is None or resp.get("stream") is None:
                    nyra_env.log_info(
                        f"GetConverseStream for input text: [{input_text}] failed"
                    )
                    return

                stream = resp.get("stream")
                sentence = ""
                full_content = ""
                first_sentence_sent = False

                for event in stream:
                    # allow 100ms buffer time, in case interruptor's flush cmd comes just after on_data event
                    if (start_time + 100_000) < self.outdate_ts:
                        nyra_env.log_info(
                            f"GetConverseStream recv interrupt and flushing for input text: [{input_text}], startTs: {start_time}, outdateTs: {self.outdate_ts}, delta > 100ms"
                        )
                        break

                    if "contentBlockDelta" in event:
                        delta_types = event["contentBlockDelta"]["delta"].keys()
                        # ignore other types of content: e.g toolUse
                        if "text" in delta_types:
                            content = event["contentBlockDelta"]["delta"]["text"]
                    elif (
                        "internalServerException" in event
                        or "modelStreamErrorException" in event
                        or "throttlingException" in event
                        or "validationException" in event
                    ):
                        nyra_env.log_error(f"GetConverseStream Error occured: {event}")
                        break
                    else:
                        # ingore other events
                        continue

                    full_content += content

                    while True:
                        sentence, content, sentence_is_final = parse_sentence(
                            sentence, content
                        )
                        if not sentence or not sentence_is_final:
                            nyra_env.log_info(f"sentence [{sentence}] is empty or not final")
                            break
                        nyra_env.log_info(
                            f"GetConverseStream recv for input text: [{input_text}] got sentence: [{sentence}]"
                        )

                        # send sentence
                        try:
                            output_data = Data.create("text_data")
                            output_data.set_property_string(
                                DATA_OUT_TEXT_DATA_PROPERTY_TEXT, sentence
                            )
                            output_data.set_property_bool(
                                DATA_OUT_TEXT_DATA_PROPERTY_TEXT_END_OF_SEGMENT, False
                            )
                            nyra_env.send_data(output_data)
                            nyra_env.log_info(
                                f"GetConverseStream recv for input text: [{input_text}] sent sentence [{sentence}]"
                            )
                        except Exception as err:
                            nyra_env.log_info(
                                f"GetConverseStream recv for input text: [{input_text}] send sentence [{sentence}] failed, err: {err}"
                            )
                            break

                        sentence = ""
                        if not first_sentence_sent:
                            first_sentence_sent = True
                            nyra_env.log_info(
                                f"GetConverseStream recv for input text: [{input_text}] first sentence sent, first_sentence_latency {get_current_time() - start_time}ms"
                            )

                if len(full_content.strip()):
                    # remember response as assistant content in memory
                    if memory and memory[-1]["role"] == "assistant":
                        memory[-1]["content"].append({"text": full_content})
                    else:
                        memory.append(
                            {"role": "assistant", "content": [{"text": full_content}]}
                        )
                else:
                    # can not put empty model response into memory
                    nyra_env.log_error(
                        f"GetConverseStream recv for input text: [{input_text}] failed: empty response [{full_content}]"
                    )
                    return

                # send end of segment
                try:
                    output_data = Data.create("text_data")
                    output_data.set_property_string(
                        DATA_OUT_TEXT_DATA_PROPERTY_TEXT, sentence
                    )
                    output_data.set_property_bool(
                        DATA_OUT_TEXT_DATA_PROPERTY_TEXT_END_OF_SEGMENT, True
                    )
                    nyra_env.send_data(output_data)
                    nyra_env.log_info(
                        f"GetConverseStream for input text: [{input_text}] end of segment with sentence [{sentence}] sent"
                    )
                except Exception as err:
                    nyra_env.log_info(
                        f"GetConverseStream for input text: [{input_text}] end of segment with sentence [{sentence}] send failed, err: {err}"
                    )

            except Exception as e:
                nyra_env.log_info(
                    f"GetConverseStream for input text: [{input_text}] failed, err: {e}"
                )

        # Start thread to request and read responses from OpenAI
        start_time = get_current_time()
        thread = Thread(
            target=converse_stream_worker, args=(start_time, input_text, self.memory)
        )
        thread.start()
        nyra_env.log_info("BedrockLLMExtension on_data end")


@register_addon_as_extension("bedrock_llm_python")
class BedrockLLMExtensionAddon(Addon):
    def on_create_instance(self, ten: TenEnv, addon_name: str, context) -> None:
        ten.log_info("on_create_instance")
        ten.on_create_instance_done(BedrockLLMExtension(addon_name), context)
