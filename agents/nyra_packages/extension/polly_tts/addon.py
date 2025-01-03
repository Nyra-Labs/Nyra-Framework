#
# This file is part of NYRA Framework, an open source project.
# Licensed under the Apache License, Version 2.0.
# See the LICENSE file for more information.
#
from ten import (
    Addon,
    register_addon_as_extension,
    TenEnv,
)

@register_addon_as_extension("polly_tts")
class PollyTTSExtensionAddon(Addon):
    def on_create_instance(self, nyra_env: TenEnv, name: str, context) -> None:
        from .extension import PollyTTSExtension
        nyra_env.log_info("polly tts on_create_instance")
        nyra_env.on_create_instance_done(PollyTTSExtension(name), context)
