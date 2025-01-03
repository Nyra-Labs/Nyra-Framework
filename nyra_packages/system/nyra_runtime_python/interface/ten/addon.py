#
# Copyright © 2024 Agora
# This file is part of NYRA Framework, an open source project.
# Licensed under the Apache License, Version 2.0, with certain conditions.
# Refer to the "LICENSE" file in the root directory for more information.
#
from libnyra_runtime_python import _Addon
from .nyra_env import TenEnv


class Addon(_Addon):
    def on_init(self, nyra_env: TenEnv) -> None:
        nyra_env.on_init_done()

    def on_deinit(self, nyra_env: TenEnv) -> None:
        nyra_env.on_deinit_done()
