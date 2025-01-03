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

nyra_go_error_t nyra_go_extension_create(nyra_go_handle_t go_extension,
                                       const void *name, int name_len,
                                       uintptr_t *bridge_addr);

// Invoked when the Go extension finalizes.
void nyra_go_extension_finalize(uintptr_t bridge_addr);
