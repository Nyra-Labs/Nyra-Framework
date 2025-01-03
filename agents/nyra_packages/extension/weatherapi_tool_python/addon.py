#
#
# Agora Real Time Engagement
# Created by Tomas Liu in 2024-08.
# Copyright (c) 2024 Agora IO. All rights reserved.
#
#
from ten import (
    Addon,
    register_addon_as_extension,
    TenEnv,
)


@register_addon_as_extension("weatherapi_tool_python")
class WeatherToolExtensionAddon(Addon):

    def on_create_instance(self, nyra_env: TenEnv, name: str, context) -> None:
        from .extension import WeatherToolExtension
        nyra_env.log_info("WeatherToolExtensionAddon on_create_instance")
        nyra_env.on_create_instance_done(WeatherToolExtension(name), context)
