//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include "nyra_runtime/nyra_env/internal/on_xxx_done.h"
#include "nyra_runtime/nyra_env/nyra_env.h"
#include "nyra_utils/lib/path.h"  // IWYU pragma: export
#include "nyra_utils/macro/ctor.h"

#define NYRA_ADDON_REGISTER(TYPE, NAME, ADDON)                          \
  NYRA_CONSTRUCTOR(____ctor_nyra_declare_##NAME##_##TYPE##_addon____) {  \
    nyra_string_t *base_dir = nyra_path_get_module_path(                 \
        (void *)____ctor_nyra_declare_##NAME##_##TYPE##_addon____);     \
    nyra_addon_register_##TYPE(#NAME, nyra_string_get_raw_str(base_dir), \
                              (ADDON));                                \
    nyra_string_destroy(base_dir);                                      \
  }                                                                    \
  NYRA_DESTRUCTOR(____dtor_nyra_declare_##NAME##_##TYPE##_addon____) {   \
    nyra_addon_unregister_##TYPE(#NAME);                                \
  }

typedef struct nyra_addon_t nyra_addon_t;
typedef struct nyra_env_t nyra_env_t;

typedef void (*nyra_addon_on_init_func_t)(nyra_addon_t *addon,
                                         nyra_env_t *nyra_env);

typedef void (*nyra_addon_on_deinit_func_t)(nyra_addon_t *addon,
                                           nyra_env_t *nyra_env);

typedef void (*nyra_addon_on_create_instance_func_t)(nyra_addon_t *addon,
                                                    nyra_env_t *nyra_env,
                                                    const char *name,
                                                    void *context);

typedef void (*nyra_addon_on_destroy_instance_func_t)(nyra_addon_t *addon,
                                                     nyra_env_t *nyra_env,
                                                     void *instance,
                                                     void *context);

typedef void (*nyra_addon_on_destroy_func_t)(nyra_addon_t *addon);

NYRA_RUNTIME_API nyra_addon_t *nyra_addon_create(
    nyra_addon_on_init_func_t on_init, nyra_addon_on_deinit_func_t on_deinit,
    nyra_addon_on_create_instance_func_t on_create_instance,
    nyra_addon_on_destroy_instance_func_t on_destroy_instance,
    nyra_addon_on_destroy_func_t on_destroy);

NYRA_RUNTIME_API void nyra_addon_init(
    nyra_addon_t *self, nyra_addon_on_init_func_t on_init,
    nyra_addon_on_deinit_func_t on_deinit,
    nyra_addon_on_create_instance_func_t on_create_instance,
    nyra_addon_on_destroy_instance_func_t on_destroy_instance,
    nyra_addon_on_destroy_func_t on_destroy);

NYRA_RUNTIME_API void nyra_addon_destroy(nyra_addon_t *self);
