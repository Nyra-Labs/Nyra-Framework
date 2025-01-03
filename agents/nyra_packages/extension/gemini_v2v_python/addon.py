#
#
# Agora Real Time Engagement
# Created by Wei Hu in 2024-08.
# Copyright (c) 2024 Agora IO. All rights reserved.
#
#
from ten import (
    Addon,
    register_addon_as_extension,
    TenEnv,
)


@register_addon_as_extension("gemini_v2v_python")
class GeminiRealtimeExtensionAddon(Addon):

    def on_create_instance(self, nyra_env: TenEnv, name: str, context) -> None:
        from .extension import GeminiRealtimeExtension
        nyra_env.log_info("GeminiRealtimeExtensionAddon on_create_instance")
        nyra_env.on_create_instance_done(GeminiRealtimeExtension(name), context)
