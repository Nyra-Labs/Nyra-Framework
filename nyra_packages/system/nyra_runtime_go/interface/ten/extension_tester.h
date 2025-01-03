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

nyra_go_error_t nyra_go_extension_tester_create(
    nyra_go_handle_t go_extension_tester, uintptr_t *bridge_addr);

void nyra_go_extension_tester_finalize(uintptr_t bridge_addr);
