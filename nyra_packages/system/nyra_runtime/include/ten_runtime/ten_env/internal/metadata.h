//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include "nyra_runtime/nyra_env/nyra_env.h"
#include "nyra_utils/value/value.h"

typedef struct nyra_env_t nyra_env_t;
typedef struct nyra_error_t nyra_error_t;

typedef void (*nyra_env_peek_property_async_cb_t)(nyra_env_t *nyra_env,
                                                 nyra_value_t *value,
                                                 void *cb_data,
                                                 nyra_error_t *err);

typedef void (*nyra_env_set_property_async_cb_t)(nyra_env_t *nyra_env, bool res,
                                                void *cb_data,
                                                nyra_error_t *err);

/**
 * @brief Note that the ownership of @a value would be transferred into the
 * NYRA runtime, so the caller of this function could _not_ consider the
 * value instance is still valid.
 */
NYRA_RUNTIME_API bool nyra_env_set_property(nyra_env_t *self, const char *path,
                                          nyra_value_t *value, nyra_error_t *err);

// This function is used to set prop on any threads.
NYRA_RUNTIME_API bool nyra_env_set_property_async(
    nyra_env_t *self, const char *path, nyra_value_t *value,
    nyra_env_set_property_async_cb_t cb, void *cb_data, nyra_error_t *err);

NYRA_RUNTIME_API nyra_value_t *nyra_env_peek_property(nyra_env_t *self,
                                                   const char *path,
                                                   nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_peek_property_async(
    nyra_env_t *self, const char *path, nyra_env_peek_property_async_cb_t cb,
    void *cb_data, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_is_property_exist(nyra_env_t *self,
                                               const char *path,
                                               nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_init_property_from_json(nyra_env_t *self,
                                                     const char *json_str,
                                                     nyra_error_t *err);
