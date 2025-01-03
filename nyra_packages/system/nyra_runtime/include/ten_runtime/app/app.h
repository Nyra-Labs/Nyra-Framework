//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include <stdbool.h>

#include "nyra_utils/lib/error.h"

typedef struct nyra_app_t nyra_app_t;
typedef struct nyra_metadata_info_t nyra_metadata_info_t;
typedef struct nyra_env_t nyra_env_t;

typedef void (*nyra_app_on_configure_func_t)(nyra_app_t *app, nyra_env_t *nyra_env);

typedef void (*nyra_app_on_init_func_t)(nyra_app_t *app, nyra_env_t *nyra_env);

typedef void (*nyra_app_on_deinit_func_t)(nyra_app_t *app, nyra_env_t *nyra_env);

NYRA_RUNTIME_API nyra_app_t *nyra_app_create(
    nyra_app_on_configure_func_t on_configure, nyra_app_on_init_func_t on_init,
    nyra_app_on_deinit_func_t on_deinit, nyra_error_t *err);

NYRA_RUNTIME_API void nyra_app_destroy(nyra_app_t *self);

NYRA_RUNTIME_API bool nyra_app_close(nyra_app_t *self, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_app_run(nyra_app_t *self, bool run_in_background,
                                 nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_app_wait(nyra_app_t *self, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_app_check_integrity(nyra_app_t *self,
                                             bool check_thread);

NYRA_RUNTIME_API nyra_env_t *nyra_app_get_nyra_env(nyra_app_t *self);

NYRA_RUNTIME_API void nyra_app_add_nyra_package_base_dir(nyra_app_t *self,
                                                      const char *base_dir);
