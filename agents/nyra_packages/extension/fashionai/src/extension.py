#
#
# Agora Real Time Engagement
# Created by Wei Hu in 2024-08.
# Copyright (c) 2024 Agora IO. All rights reserved.
#
#
import traceback
from ten import (
    AudioFrame,
    VideoFrame,
    AsyncTenEnv,
    Cmd,
    StatusCode,
    CmdResult,
    Data,
)
from ten.async_extension import AsyncExtension

import asyncio
from .fashionai_client import FashionAIClient
from datetime import datetime


class FashionAIExtension(AsyncExtension):

    def __init__(self, name: str):
        super().__init__(name)

        self.app_id = ""
        self.token = ""
        self.channel = ""
        self.stream_id = 0
        self.service_id = "agora"
        self.stopped = False
        self.queue = None
        self.client = None
        self.outdate_ts = datetime.now()

    async def on_init(self, nyra_env: AsyncTenEnv) -> None:
        nyra_env.log_info(
            "FASHION_AI on_init *********************************************************"
        )
        self.stopped = False
        self.queue = asyncio.Queue(maxsize=3000)

    async def on_start(self, nyra_env: AsyncTenEnv) -> None:
        nyra_env.log_info(
            "FASHION_AI on_start *********************************************************"
        )

        try:
            self.app_id = await nyra_env.get_property_string("app_id")
            self.token = await nyra_env.get_property_string("token")
            self.channel = await nyra_env.get_property_string("channel")
            self.stream_id = str(await nyra_env.get_property_int("stream_id"))
            self.service_id = await nyra_env.get_property_string("service_id")

            nyra_env.log_info(
                f"FASHION_AI on_start: app_id = {self.app_id}, token = {self.token}, channel = {self.channel}, stream_id = {self.stream_id}, service_id = {self.service_id}"
            )
        except Exception as e:
            nyra_env.log_warn(f"get_property err: {e}")

        if len(self.token) > 0:
            self.app_id = self.token
        self.client = FashionAIClient(
            nyra_env,
            "wss://ingress.service.fasionai.com/websocket/node5/agoramultimodel2",
            self.service_id,
        )
        asyncio.create_task(self.process_input_text(nyra_env))
        await self.init_fashionai(self.app_id, self.channel, self.stream_id)

    async def on_stop(self, nyra_env: AsyncTenEnv) -> None:
        nyra_env.log_info("FASHION_AI on_stop")
        self.stopped = True
        await self.queue.put(None)

    async def on_deinit(self, nyra_env: AsyncTenEnv) -> None:
        nyra_env.log_info("FASHION_AI on_deinit")

    async def on_cmd(self, nyra_env: AsyncTenEnv, cmd: Cmd) -> None:
        cmd_name = cmd.get_name()
        nyra_env.log_info(f"FASHION_AI on_cmd name {cmd_name}")

        if cmd_name == "flush":
            self.outdate_ts = datetime.now()
            try:
                await self.client.send_interrupt()

            except Exception:
                nyra_env.log_warn(f"flush err: {traceback.format_exc()}")

            cmd_out = Cmd.create("flush")
            await nyra_env.send_cmd(cmd_out)
            # nyra_env.send_cmd(cmd_out, lambda ten, result: nyra_env.log_info("send_cmd flush done"))
        else:
            nyra_env.log_info(f"unknown cmd {cmd_name}")

        nyra_env.log_info("FASHION_AI on_cmd done")
        cmd_result = CmdResult.create(StatusCode.OK)
        await nyra_env.return_result(cmd_result, cmd)

    async def on_data(self, nyra_env: AsyncTenEnv, data: Data) -> None:
        input_text = data.get_property_string("text")
        if len(input_text) == 0:
            nyra_env.log_info("FASHION_AI ignore empty text")
            return

        nyra_env.log_info("FASHION_AI on data %s", input_text)
        try:
            await self.queue.put(input_text)
        except asyncio.TimeoutError:
            nyra_env.log_warn(f"FASHION_AI put inputText={input_text} queue timed out")
        except Exception as e:
            nyra_env.log_warn(f"FASHION_AI put inputText={input_text} queue err: {e}")
        nyra_env.log_info("FASHION_AI send_inputText %s", input_text)

    async def on_audio_frame(self, _: AsyncTenEnv, audio_frame: AudioFrame) -> None:
        pass

    async def on_video_frame(self, _: AsyncTenEnv, video_frame: VideoFrame) -> None:
        pass

    async def init_fashionai(self, app_id, channel, stream_id):
        await self.client.connect()
        await self.client.stream_start(app_id, channel, stream_id)
        await self.client.render_start()

    async def process_input_text(self, nyra_env: AsyncTenEnv):
        while True:
            input_text = await self.queue.get()
            if input_text is None:
                nyra_env.log_info("Stopping async_polly_handler...")
                break

            nyra_env.log_info(f"async_polly_handler: loop fashion ai polly.{input_text}")

            if len(input_text) > 0:
                try:
                    await self.client.send_inputText(input_text)
                except Exception as e:
                    nyra_env.log_error(str(e))
