//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>

#include "nyra_utils/lib/json.h"
#include "nyra_utils/lib/signature.h"
#include "nyra_utils/lib/string.h"

typedef struct nyra_value_t nyra_value_t;

typedef struct nyra_value_kv_t {
  nyra_signature_t signature;

  nyra_string_t key;
  nyra_value_t *value;
} nyra_value_kv_t;

NYRA_UTILS_API bool nyra_value_kv_check_integrity(nyra_value_kv_t *self);

NYRA_UTILS_API nyra_value_kv_t *nyra_value_kv_create_empty(const char *name);

NYRA_UTILS_API nyra_value_kv_t *nyra_value_kv_create(const char *name,
                                                  nyra_value_t *value);

NYRA_UTILS_API void nyra_value_kv_destroy(nyra_value_kv_t *self);

// This special destroy function for the value will only deinitialize the key
// field and will not handle the value field.
NYRA_UTILS_API void nyra_value_kv_destroy_key_only(nyra_value_kv_t *self);

NYRA_UTILS_API nyra_value_kv_t *nyra_value_kv_clone(nyra_value_kv_t *target);

NYRA_UTILS_API nyra_string_t *nyra_value_kv_get_key(nyra_value_kv_t *self);

NYRA_UTILS_API nyra_value_t *nyra_value_kv_get_value(nyra_value_kv_t *self);

NYRA_UTILS_API void nyra_value_kv_reset_to_value(nyra_value_kv_t *self,
                                               nyra_value_t *value);

NYRA_UTILS_API nyra_string_t *nyra_value_kv_to_string(nyra_value_kv_t *self,
                                                   nyra_error_t *err);

NYRA_UTILS_API nyra_value_kv_t *nyra_value_kv_from_json(const char *key,
                                                     nyra_json_t *json);

NYRA_UTILS_API void nyra_value_kv_to_json(nyra_json_t *json, nyra_value_kv_t *kv);
