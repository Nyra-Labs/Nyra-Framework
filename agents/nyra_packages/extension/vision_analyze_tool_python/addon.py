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
from .extension import VisionAnalyzeToolExtension


@register_addon_as_extension("vision_analyze_tool_python")
class VisionAnalyzeToolExtensionAddon(Addon):

    def on_create_instance(self, nyra_env: TenEnv, name: str, context) -> None:
        nyra_env.log_info("TSDBFirestoreExtensionAddon on_create_instance")
        nyra_env.on_create_instance_done(VisionAnalyzeToolExtension(name), context)
