#
# Copyright © 2024 Agora
# This file is part of NYRA Framework, an open source project.
# Licensed under the Apache License, Version 2.0, with certain conditions.
# Refer to the "LICENSE" file in the root directory for more information.
#
from enum import IntEnum


class _TenEnvAttachTo(IntEnum):
    EXNYRASION = 1
    EXNYRASION_GROUP = 2
    APP = 3
    ADDON = 4
