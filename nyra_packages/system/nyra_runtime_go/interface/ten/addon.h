//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "common.h"

void nyra_go_addon_unregister(uintptr_t bridge_addr);

nyra_go_error_t nyra_go_addon_register_extension(
    const void *addon_name, int addon_name_len, const void *base_dir,
    int base_dir_len, uintptr_t go_addon, uintptr_t *register_ctx,
    uintptr_t *bridge_addr);
