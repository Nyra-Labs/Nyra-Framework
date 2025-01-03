//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

typedef struct nyra_addon_manager_t nyra_addon_manager_t;

typedef void (*nyra_addon_registration_func_t)(void *register_ctx);

NYRA_RUNTIME_API nyra_addon_manager_t *nyra_addon_manager_get_instance(void);

NYRA_RUNTIME_API void nyra_addon_manager_add_addon(
    nyra_addon_manager_t *self, const char *name,
    nyra_addon_registration_func_t func);
