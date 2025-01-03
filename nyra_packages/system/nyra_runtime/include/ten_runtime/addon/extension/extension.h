//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include <stdbool.h>

#include "nyra_runtime/nyra_env/nyra_env.h"

#define NYRA_REGISTER_ADDON_AS_EXNYRASION(NAME, ADDON) \
  NYRA_ADDON_REGISTER(extension, NAME, ADDON)

typedef struct nyra_env_t nyra_env_t;
typedef struct nyra_addon_t nyra_addon_t;
typedef struct nyra_extension_t nyra_extension_t;
typedef struct nyra_addon_host_t nyra_addon_host_t;

typedef nyra_addon_host_t *(*nyra_addon_register_extension_func_t)(
    const char *name, const char *base_dir, nyra_addon_t *addon,
    void *register_ctx);

NYRA_RUNTIME_API nyra_addon_host_t *nyra_addon_register_extension(
    const char *name, const char *base_dir, nyra_addon_t *addon,
    void *register_ctx);

NYRA_RUNTIME_API nyra_addon_t *nyra_addon_unregister_extension(const char *name);

NYRA_RUNTIME_API bool nyra_addon_create_extension(
    nyra_env_t *nyra_env, const char *addon_name, const char *instance_name,
    nyra_env_addon_create_instance_done_cb_t cb, void *user_data,
    nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_addon_destroy_extension(
    nyra_env_t *nyra_env, nyra_extension_t *extension,
    nyra_env_addon_destroy_instance_done_cb_t cb, void *user_data,
    nyra_error_t *err);
