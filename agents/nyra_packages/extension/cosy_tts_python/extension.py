#
# This file is part of NYRA Framework, an open source project.
# Licensed under the Apache License, Version 2.0.
# See the LICENSE file for more information.
#
import asyncio
from .cosy_tts import CosyTTS, CosyTTSConfig
from ten import (
    AsyncTenEnv,
)
from nyra_ai_base.tts import AsyncTTSBaseExtension


class CosyTTSExtension(AsyncTTSBaseExtension):
    def __init__(self, name: str) -> None:
        super().__init__(name)
        self.client = None
        self.config = None

    async def on_init(self, nyra_env: AsyncTenEnv) -> None:
        await super().on_init(nyra_env)
        nyra_env.log_debug("on_init")

    async def on_start(self, nyra_env: AsyncTenEnv) -> None:
        await super().on_start(nyra_env)
        nyra_env.log_debug("on_start")

        self.config = await CosyTTSConfig.create_async(nyra_env=nyra_env)
        self.client = CosyTTS(self.config)

        asyncio.create_task(self._process_audio_data(nyra_env))

    async def on_stop(self, nyra_env: AsyncTenEnv) -> None:
        await super().on_stop(nyra_env)
        nyra_env.log_debug("on_stop")

        await self.queue.put(None)

    async def on_deinit(self, nyra_env: AsyncTenEnv) -> None:
        await super().on_deinit(nyra_env)
        nyra_env.log_debug("on_deinit")

    async def _process_audio_data(self, nyra_env: AsyncTenEnv) -> None:
        while True:
            audio_data = await self.client.get_audio_bytes()

            if audio_data is None:
                break

            await self.send_audio_out(nyra_env, audio_data)

    async def on_request_tts(
        self, nyra_env: AsyncTenEnv, input_text: str, end_of_segment: bool
    ) -> None:
        self.client.text_to_speech_stream(nyra_env, input_text, end_of_segment)

    async def on_cancel_tts(self, nyra_env: AsyncTenEnv) -> None:
        self.client.cancel(nyra_env)
