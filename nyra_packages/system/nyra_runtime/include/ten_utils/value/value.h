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
#include "nyra_utils/lib/signature.h"
#include "nyra_utils/lib/string.h"
#include "nyra_utils/value/type.h"
#include "nyra_utils/value/value_get.h"     // IWYU pragma: keep
#include "nyra_utils/value/value_is.h"      // IWYU pragma: keep
#include "nyra_utils/value/value_json.h"    // IWYU pragma: keep
#include "nyra_utils/value/value_kv.h"      // IWYU pragma: keep
#include "nyra_utils/value/value_merge.h"   // IWYU pragma: keep
#include "nyra_utils/value/value_object.h"  // IWYU pragma: keep
#include "nyra_utils/value/value_string.h"  // IWYU pragma: keep

typedef enum NYRA_VALUE_ERROR {
  NYRA_VALUE_ERROR_UNSUPPORTED_TYPE_CONVERSION = 1,
} NYRA_VALUE_ERROR;

#define nyra_value_object_foreach(value, iter) \
  nyra_list_foreach (&((value)->content.object), iter)

#define nyra_value_array_foreach(value, iter) \
  nyra_list_foreach (&((value)->content.array), iter)

typedef struct nyra_value_t nyra_value_t;

typedef union nyra_value_union_t {
  bool boolean;

  int8_t int8;
  int16_t int16;
  int32_t int32;
  int64_t int64;

  uint8_t uint8;
  uint16_t uint16;
  uint32_t uint32;
  uint64_t uint64;

  float float32;
  double float64;

  void *ptr;

  nyra_list_t object;  // The element type is 'nyra_value_kv_t*'
  nyra_list_t array;   // The element type is 'nyra_value_t*'
  nyra_string_t string;
  nyra_buf_t buf;
} nyra_value_union_t;

typedef bool (*nyra_value_construct_func_t)(nyra_value_t *value,
                                           nyra_error_t *err);

typedef bool (*nyra_value_copy_func_t)(nyra_value_t *dest, nyra_value_t *src,
                                      nyra_error_t *err);

typedef bool (*nyra_value_destruct_func_t)(nyra_value_t *value, nyra_error_t *err);

typedef struct nyra_value_t {
  nyra_signature_t signature;

  /**
   * @brief The name of the value. Mainly for debug purpose.
   */
  nyra_string_t *name;

  NYRA_TYPE type;
  nyra_value_union_t content;

  nyra_value_construct_func_t construct;
  nyra_value_copy_func_t copy;
  nyra_value_destruct_func_t destruct;
} nyra_value_t;

NYRA_UTILS_API bool nyra_value_check_integrity(nyra_value_t *self);

NYRA_UTILS_API nyra_value_t *nyra_value_clone(nyra_value_t *src);
NYRA_UTILS_API bool nyra_value_copy(nyra_value_t *src, nyra_value_t *dest);

NYRA_UTILS_API bool nyra_value_init_invalid(nyra_value_t *self);
NYRA_UTILS_API bool nyra_value_init_int8(nyra_value_t *self, int8_t value);
NYRA_UTILS_API bool nyra_value_init_int16(nyra_value_t *self, int16_t value);
NYRA_UTILS_API bool nyra_value_init_int32(nyra_value_t *self, int32_t value);
NYRA_UTILS_API bool nyra_value_init_int64(nyra_value_t *self, int64_t value);
NYRA_UTILS_API bool nyra_value_init_uint8(nyra_value_t *self, uint8_t value);
NYRA_UTILS_API bool nyra_value_init_uint16(nyra_value_t *self, uint16_t value);
NYRA_UTILS_API bool nyra_value_init_uint32(nyra_value_t *self, uint32_t value);
NYRA_UTILS_API bool nyra_value_init_uint64(nyra_value_t *self, uint64_t value);
NYRA_UTILS_API bool nyra_value_init_float32(nyra_value_t *self, float value);
NYRA_UTILS_API bool nyra_value_init_float64(nyra_value_t *self, double value);
NYRA_UTILS_API bool nyra_value_init_bool(nyra_value_t *self, bool value);
NYRA_UTILS_API bool nyra_value_init_null(nyra_value_t *self);
NYRA_UTILS_API bool nyra_value_init_string(nyra_value_t *self);
NYRA_UTILS_API bool nyra_value_init_string_with_size(nyra_value_t *self,
                                                   const char *str, size_t len);
NYRA_UTILS_API bool nyra_value_init_buf(nyra_value_t *self, size_t size);

/**
 * @note Note that the ownership of @a value is moved to the value @a self.
 */
NYRA_UTILS_API bool nyra_value_init_object_with_move(nyra_value_t *self,
                                                   nyra_list_t *value);

/**
 * @note Note that the ownership of @a value is moved to the value @a self.
 */
NYRA_UTILS_API bool nyra_value_init_array_with_move(nyra_value_t *self,
                                                  nyra_list_t *value);

NYRA_UTILS_API nyra_value_t *nyra_value_create_invalid(void);
NYRA_UTILS_API nyra_value_t *nyra_value_create_int8(int8_t value);
NYRA_UTILS_API nyra_value_t *nyra_value_create_int16(int16_t value);
NYRA_UTILS_API nyra_value_t *nyra_value_create_int32(int32_t value);
NYRA_UTILS_API nyra_value_t *nyra_value_create_int64(int64_t value);
NYRA_UTILS_API nyra_value_t *nyra_value_create_uint8(uint8_t value);
NYRA_UTILS_API nyra_value_t *nyra_value_create_uint16(uint16_t value);
NYRA_UTILS_API nyra_value_t *nyra_value_create_uint32(uint32_t value);
NYRA_UTILS_API nyra_value_t *nyra_value_create_uint64(uint64_t value);
NYRA_UTILS_API nyra_value_t *nyra_value_create_float32(float value);
NYRA_UTILS_API nyra_value_t *nyra_value_create_float64(double value);
NYRA_UTILS_API nyra_value_t *nyra_value_create_bool(bool value);
NYRA_UTILS_API nyra_value_t *nyra_value_create_array_with_move(nyra_list_t *value);
NYRA_UTILS_API nyra_value_t *nyra_value_create_object_with_move(nyra_list_t *value);
NYRA_UTILS_API nyra_value_t *nyra_value_create_string_with_size(const char *str,
                                                             size_t len);
NYRA_UTILS_API nyra_value_t *nyra_value_create_string(const char *str);
NYRA_UTILS_API nyra_value_t *nyra_value_create_null(void);
NYRA_UTILS_API nyra_value_t *nyra_value_create_ptr(
    void *ptr, nyra_value_construct_func_t construct, nyra_value_copy_func_t copy,
    nyra_value_destruct_func_t destruct);
NYRA_UTILS_API nyra_value_t *nyra_value_create_buf_with_move(nyra_buf_t buf);

NYRA_UTILS_API void nyra_value_deinit(nyra_value_t *self);

NYRA_UTILS_API void nyra_value_destroy(nyra_value_t *self);

NYRA_UTILS_API void nyra_value_reset_to_string_with_size(nyra_value_t *self,
                                                       const char *str,
                                                       size_t len);

NYRA_UTILS_API void nyra_value_reset_to_ptr(nyra_value_t *self, void *ptr,
                                          nyra_value_construct_func_t construct,
                                          nyra_value_copy_func_t copy,
                                          nyra_value_destruct_func_t destruct);

NYRA_UTILS_API void nyra_value_set_name(nyra_value_t *self, const char *fmt, ...);

NYRA_UTILS_API size_t nyra_value_array_size(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_is_valid(nyra_value_t *self);
