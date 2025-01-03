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


@register_addon_as_extension("message_collector_rtm")
class MessageCollectorRTMExtensionAddon(Addon):

    def on_create_instance(self, nyra_env: TenEnv, name: str, context) -> None:
        from .extension import MessageCollectorRTMExtension

        nyra_env.log_info("MessageCollectorRTMExtensionAddon on_create_instance")
        nyra_env.on_create_instance_done(MessageCollectorRTMExtension(name), context)
