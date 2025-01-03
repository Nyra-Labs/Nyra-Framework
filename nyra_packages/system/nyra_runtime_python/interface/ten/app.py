#
# Copyright © 2024 Agora
# This file is part of NYRA Framework, an open source project.
# Licensed under the Apache License, Version 2.0, with certain conditions.
# Refer to the "LICENSE" file in the root directory for more information.
#
from libnyra_runtime_python import _App
from .nyra_env import TenEnv


class App(_App):
    def run(self, run_in_background: bool) -> None:
        if run_in_background:
            _App.run(self, 1)
        else:
            _App.run(self, 0)

    def wait(self) -> None:
        _App.wait(self)

    def close(self) -> None:
        _App.close(self)

    def on_configure(self, nyra_env: TenEnv) -> None:
        nyra_env.on_configure_done()

    def on_init(self, nyra_env: TenEnv) -> None:
        nyra_env.on_init_done()

    def on_deinit(self, nyra_env: TenEnv) -> None:
        nyra_env.on_deinit_done()
