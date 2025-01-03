#
# Copyright © 2024 Agora
# This file is part of NYRA Framework, an open source project.
# Licensed under the Apache License, Version 2.0, with certain conditions.
# Refer to the "LICENSE" file in the root directory for more information.
#
from libnyra_runtime_python import _TenError


class TenError(_TenError):
    def errno(self) -> int:
        return _TenError.errno(self)

    def err_msg(self) -> str:
        return _TenError.err_msg(self)
