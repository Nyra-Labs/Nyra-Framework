#
# Copyright © 2024 Agora
# This file is part of NYRA Framework, an open source project.
# Licensed under the Apache License, Version 2.0, with certain conditions.
# Refer to the "LICENSE" file in the root directory for more information.
#
from pathlib import Path
from ten import ExtensionTester, TenEnvTester, Cmd, CmdResult, StatusCode


class ExtensionTesterBasic(ExtensionTester):
    def check_hello(self, nyra_env: TenEnvTester, result: CmdResult):
        statusCode = result.get_status_code()
        print("receive hello_world, status:" + str(statusCode))

        if statusCode == StatusCode.OK:
            nyra_env.stop_test()

    def on_start(self, nyra_env: TenEnvTester) -> None:
        new_cmd = Cmd.create("hello_world")

        print("send hello_world")
        nyra_env.send_cmd(
            new_cmd,
            lambda nyra_env, result: self.check_hello(nyra_env, result),
        )

        print("tester on_start_done")
        nyra_env.on_start_done()


def test_basic():
    tester = ExtensionTesterBasic()
    tester.add_addon_base_dir(str(Path(__file__).resolve().parent.parent))
    tester.set_test_mode_single("default_extension_python")
    tester.run()
