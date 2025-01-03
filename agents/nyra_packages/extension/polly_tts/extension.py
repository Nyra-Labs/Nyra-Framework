from nyra_ai_base.tts import AsyncTTSBaseExtension
from .polly_tts import PollyTTS, PollyTTSConfig
import traceback
from ten import (
    AsyncTenEnv,
)

PROPERTY_REGION = "region"  # Optional
PROPERTY_ACCESS_KEY = "access_key"  # Optional
PROPERTY_SECRET_KEY = "secret_key"  # Optional
PROPERTY_ENGINE = "engine"  # Optional
PROPERTY_VOICE = "voice"  # Optional
PROPERTY_SAMPLE_RATE = "sample_rate"  # Optional
PROPERTY_LANG_CODE = "lang_code"  # Optional


class PollyTTSExtension(AsyncTTSBaseExtension):
    def __init__(self, name: str):
        super().__init__(name)
        self.client = None
        self.config = None

    async def on_init(self, nyra_env: AsyncTenEnv) -> None:
        await super().on_init(nyra_env)
        nyra_env.log_debug("on_init")

    async def on_start(self, nyra_env: AsyncTenEnv) -> None:
        try:
            await super().on_start(nyra_env)
            nyra_env.log_debug("on_start")
            self.config = await PollyTTSConfig.create_async(nyra_env=nyra_env)

            if not self.config.access_key or not self.config.secret_key:
                raise ValueError("access_key and secret_key are required")

            self.client = PollyTTS(self.config, nyra_env)
        except Exception:
            nyra_env.log_error(f"on_start failed: {traceback.format_exc()}")

    async def on_stop(self, nyra_env: AsyncTenEnv) -> None:
        await super().on_stop(nyra_env)
        nyra_env.log_debug("on_stop")

        # TODO: clean up resources

    async def on_deinit(self, nyra_env: AsyncTenEnv) -> None:
        await super().on_deinit(nyra_env)
        nyra_env.log_debug("on_deinit")

    async def on_request_tts(
        self, nyra_env: AsyncTenEnv, input_text: str, end_of_segment: bool
    ) -> None:
        try:
            data = self.client.text_to_speech_stream(nyra_env, input_text)
            async for frame in data:
                await self.send_audio_out(
                    nyra_env, frame, sample_rate=self.client.config.sample_rate
                )
        except Exception:
            nyra_env.log_error(f"on_request_tts failed: {traceback.format_exc()}")

    async def on_cancel_tts(self, nyra_env: AsyncTenEnv) -> None:
        return await super().on_cancel_tts(nyra_env)
