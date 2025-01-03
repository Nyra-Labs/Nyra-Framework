//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include "nyra_utils/lib/string.h"

/**
 * @brief Dynamicly load a module.
 * @param name The name of the module to load.
 * @param as_local If true, the module will be loaded as RTLD_LOCAL, RTLD_GLOBAL
 *                 otherwise
 * @return The handle of the loaded module, or NULL on failure.
 * @note On iOS and Android, this function do nothing and will assert your app
 *       in debug mode.
 */
NYRA_UTILS_API void *nyra_module_load(const nyra_string_t *name, int as_local);

/**
 * @brief Unload a module.
 * @param handle The handle of the module to unload.
 * @return 0 on success, or -1 on failure.
 */
NYRA_UTILS_API int nyra_module_close(void *handle);

NYRA_UTILS_API void *nyra_module_get_symbol(void *handle,
                                          const char *symbol_name);
