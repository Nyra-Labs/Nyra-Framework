//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>
#include <stdint.h>

#include "nyra_utils/lib/error.h"
#include "nyra_utils/value/value_kv.h"

NYRA_UTILS_API nyra_value_t *nyra_value_object_peek(nyra_value_t *self,
                                                 const char *key);

NYRA_UTILS_API bool nyra_value_object_get_bool(nyra_value_t *self, const char *key,
                                             nyra_error_t *err);

NYRA_UTILS_API const char *nyra_value_object_peek_string(nyra_value_t *self,
                                                       const char *key);

NYRA_UTILS_API nyra_list_t *nyra_value_object_peek_array(nyra_value_t *self,
                                                      const char *key);

/**
 * @note Note that the ownership of @a value is moved to the value @a self.
 */
NYRA_UTILS_API bool nyra_value_object_move(nyra_value_t *self, const char *key,
                                         nyra_value_t *value);
