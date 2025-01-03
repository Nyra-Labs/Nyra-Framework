#
# This file is part of NYRA Framework, an open source project.
# Licensed under the Apache License, Version 2.0.
# See the LICENSE file for more information.
#
import traceback
from .elevenlabs_tts import ElevenLabsTTS, ElevenLabsTTSConfig
from ten import (
    AsyncTenEnv,
)
from nyra_ai_base.tts import AsyncTTSBaseExtension


class ElevenLabsTTSExtension(AsyncTTSBaseExtension):
    def __init__(self, name: str) -> None:
        super().__init__(name)
        self.config = None
        self.client = None

    async def on_init(self, nyra_env: AsyncTenEnv) -> None:
        await super().on_init(nyra_env)
        nyra_env.log_debug("on_init")

    async def on_start(self, nyra_env: AsyncTenEnv) -> None:
        try:
            await super().on_start(nyra_env)
            nyra_env.log_debug("on_start")
            self.config = await ElevenLabsTTSConfig.create_async(nyra_env=nyra_env)

            if not self.config.api_key:
                raise ValueError("api_key is required")

            self.client = ElevenLabsTTS(self.config)
        except Exception:
            nyra_env.log_error(f"on_start failed: {traceback.format_exc()}")

    async def on_stop(self, nyra_env: AsyncTenEnv) -> None:
        await super().on_stop(nyra_env)
        nyra_env.log_debug("on_stop")

    async def on_deinit(self, nyra_env: AsyncTenEnv) -> None:
        await super().on_deinit(nyra_env)
        nyra_env.log_debug("on_deinit")

    async def on_request_tts(
        self, nyra_env: AsyncTenEnv, input_text: str, end_of_segment: bool
    ) -> None:
        audio_stream = await self.client.text_to_speech_stream(input_text)
        nyra_env.log_info(f"on_request_tts: {input_text}")
        async for audio_data in audio_stream:
            await self.send_audio_out(nyra_env, audio_data)
        nyra_env.log_info(f"on_request_tts: {input_text} done")

    async def on_cancel_tts(self, nyra_env: AsyncTenEnv) -> None:
        return await super().on_cancel_tts(nyra_env)
