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


@register_addon_as_extension("openai_chatgpt_python")
class OpenAIChatGPTExtensionAddon(Addon):

    def on_create_instance(self, nyra_env: TenEnv, name: str, context) -> None:
        from .extension import OpenAIChatGPTExtension
        nyra_env.log_info("OpenAIChatGPTExtensionAddon on_create_instance")
        nyra_env.on_create_instance_done(OpenAIChatGPTExtension(name), context)