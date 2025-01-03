//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>

#include "nyra_utils/value/value_kv.h"

NYRA_UTILS_API bool nyra_value_is_object(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_array(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_string(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_invalid(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_int8(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_int16(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_int32(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_int64(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_uint8(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_uint16(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_uint32(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_uint64(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_float32(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_float64(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_number(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_null(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_bool(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_ptr(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_buf(nyra_value_t *self);
