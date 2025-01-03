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


@register_addon_as_extension("cartesia_tts")
class CartesiaTTSExtensionAddon(Addon):

    def on_create_instance(self, nyra_env: TenEnv, name: str, context) -> None:
        from .extension import CartesiaTTSExtension
        nyra_env.log_info("CartesiaTTSExtensionAddon on_create_instance")
        nyra_env.on_create_instance_done(CartesiaTTSExtension(name), context)
