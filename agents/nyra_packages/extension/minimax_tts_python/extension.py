#
# This file is part of NYRA Framework, an open source project.
# Licensed under the Apache License, Version 2.0.
# See the LICENSE file for more information.
#
import traceback
from nyra_ai_base.tts import AsyncTTSBaseExtension
from .minimax_tts import MinimaxTTS, MinimaxTTSConfig
from ten import (
    AsyncTenEnv,
)


class MinimaxTTSExtension(AsyncTTSBaseExtension):
    def __init__(self, name: str):
        super().__init__(name)
        self.client = None

    async def on_init(self, nyra_env: AsyncTenEnv) -> None:
        await super().on_init(nyra_env)
        nyra_env.log_debug("on_init")

    async def on_start(self, nyra_env: AsyncTenEnv) -> None:
        await super().on_start(nyra_env)
        nyra_env.log_debug("on_start")

        config = await MinimaxTTSConfig.create_async(nyra_env=nyra_env)

        nyra_env.log_info(f"config: {config.api_key}, {config.group_id}")

        if not config.api_key or not config.group_id:
            raise ValueError("api_key and group_id are required")

        self.client = MinimaxTTS(config)

    async def on_stop(self, nyra_env: AsyncTenEnv) -> None:
        await super().on_stop(nyra_env)
        nyra_env.log_debug("on_stop")

    async def on_deinit(self, nyra_env: AsyncTenEnv) -> None:
        await super().on_deinit(nyra_env)
        nyra_env.log_debug("on_deinit")

    async def on_request_tts(
        self, nyra_env: AsyncTenEnv, input_text: str, end_of_segment: bool
    ) -> None:
        try:
            data = self.client.get(nyra_env, input_text)
            async for frame in data:
                await self.send_audio_out(
                    nyra_env, frame, sample_rate=self.client.config.sample_rate
                )
        except Exception:
            nyra_env.log_error(f"on_request_tts failed: {traceback.format_exc()}")

    async def on_cancel_tts(self, nyra_env: AsyncTenEnv) -> None:
        return await super().on_cancel_tts(nyra_env)
