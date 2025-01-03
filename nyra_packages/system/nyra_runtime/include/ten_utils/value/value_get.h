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

#include "nyra_utils/container/list.h"
#include "nyra_utils/lib/buf.h"
#include "nyra_utils/lib/error.h"
#include "nyra_utils/lib/string.h"
#include "nyra_utils/value/type.h"
#include "nyra_utils/value/value_kv.h"

NYRA_UTILS_API NYRA_TYPE nyra_value_get_type(nyra_value_t *self);

NYRA_UTILS_API int8_t nyra_value_get_int8(nyra_value_t *self, nyra_error_t *err);

NYRA_UTILS_API int16_t nyra_value_get_int16(nyra_value_t *self, nyra_error_t *err);

NYRA_UTILS_API int32_t nyra_value_get_int32(nyra_value_t *self, nyra_error_t *err);

NYRA_UTILS_API int64_t nyra_value_get_int64(nyra_value_t *self, nyra_error_t *err);

NYRA_UTILS_API uint8_t nyra_value_get_uint8(nyra_value_t *self, nyra_error_t *err);

NYRA_UTILS_API uint16_t nyra_value_get_uint16(nyra_value_t *self,
                                            nyra_error_t *err);

NYRA_UTILS_API uint32_t nyra_value_get_uint32(nyra_value_t *self,
                                            nyra_error_t *err);

NYRA_UTILS_API uint64_t nyra_value_get_uint64(nyra_value_t *self,
                                            nyra_error_t *err);

NYRA_UTILS_API float nyra_value_get_float32(nyra_value_t *self, nyra_error_t *err);

NYRA_UTILS_API double nyra_value_get_float64(nyra_value_t *self, nyra_error_t *err);

NYRA_UTILS_API bool nyra_value_get_bool(nyra_value_t *self, nyra_error_t *err);

NYRA_UTILS_API nyra_string_t *nyra_value_peek_string(nyra_value_t *self);

NYRA_UTILS_API const char *nyra_value_peek_raw_str(nyra_value_t *self,
                                                 nyra_error_t *err);

NYRA_UTILS_API void *nyra_value_get_ptr(nyra_value_t *self, nyra_error_t *err);

NYRA_UTILS_API nyra_buf_t *nyra_value_peek_buf(nyra_value_t *self);

NYRA_UTILS_API nyra_list_t *nyra_value_peek_array(nyra_value_t *self);

NYRA_UTILS_API nyra_list_t *nyra_value_peek_object(nyra_value_t *self);

NYRA_UTILS_API nyra_value_t *nyra_value_array_peek(nyra_value_t *self, size_t index,
                                                nyra_error_t *err);
