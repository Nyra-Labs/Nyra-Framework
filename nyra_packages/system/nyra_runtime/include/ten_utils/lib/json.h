//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "nyra_utils/lib/error.h"
#include "nyra_utils/value/type.h"

typedef struct json_t json_t;
typedef json_t nyra_json_t;

#define nyra_json_array_foreach(array, index, value)                     \
  for ((index) = 0; (index) < nyra_json_array_get_size(array) &&         \
                    ((value) = nyra_json_array_peek_item(array, index)); \
       (index)++)

#define nyra_json_object_foreach(object, key, value)                    \
  for ((key) = nyra_json_object_iter_key(nyra_json_object_iter(object)); \
       (key) && ((value) = nyra_json_object_iter_value(                 \
                     nyra_json_object_key_to_iter(key)));               \
       (key) = nyra_json_object_iter_key(nyra_json_object_iter_next(     \
           object, nyra_json_object_key_to_iter(key))))

NYRA_UTILS_API bool nyra_json_check_integrity(nyra_json_t *json);

/**
 * @brief delete the item from json object specified by key.
 * @param json json object
 * @param field key name
 * @return true if key exists and delete successful, false otherwise
 */
NYRA_UTILS_API bool nyra_json_object_del(nyra_json_t *json, const char *field);

NYRA_UTILS_API NYRA_TYPE nyra_json_get_type(nyra_json_t *json);

/**
 * @brief get string value from json object
 * @param json json object
 * @param field key
 * @return value if exists, NULL otherwise
 */
NYRA_UTILS_API const char *nyra_json_object_peek_string(nyra_json_t *json,
                                                      const char *field);

/**
 * @brief get int value from json object
 * @param json json object
 * @param field key
 * @return value if exists, -1 otherwise
 */
NYRA_UTILS_API int64_t nyra_json_object_get_integer(nyra_json_t *json,
                                                  const char *field);

/**
 * @brief get floating-point value from json object
 * @param json json object
 * @param field key
 * @return value if exists, 0 otherwise
 */
NYRA_UTILS_API double nyra_json_object_get_real(nyra_json_t *json,
                                              const char *field);

/**
 * @brief get boolean value from json object
 * @param json json object
 * @param field key
 * @return value if exists, false otherwise
 */
NYRA_UTILS_API bool nyra_json_object_get_boolean(nyra_json_t *json,
                                               const char *field);

NYRA_UTILS_API nyra_json_t *nyra_json_object_peek_array(nyra_json_t *json,
                                                     const char *field);

NYRA_UTILS_API nyra_json_t *nyra_json_object_peek_array_forcibly(
    nyra_json_t *json, const char *field);

NYRA_UTILS_API nyra_json_t *nyra_json_object_peek_object(nyra_json_t *json,
                                                      const char *field);

NYRA_UTILS_API nyra_json_t *nyra_json_object_peek_object_forcibly(
    nyra_json_t *json, const char *field);

NYRA_UTILS_API void nyra_json_object_set_new(nyra_json_t *json, const char *field,
                                           nyra_json_t *value);

NYRA_UTILS_API void nyra_json_array_append_new(nyra_json_t *json,
                                             nyra_json_t *value);

/**
 * @brief check if json object contains a field
 * @param json json object
 * @param field key
 * @return non-NULL if exists, NULL otherwise
 */
NYRA_UTILS_API nyra_json_t *nyra_json_object_peek(nyra_json_t *json,
                                               const char *field);

/**
 * @brief Get value of field from json object in string format, if the type
 *        of field is not string, dumps the value in string format.
 * @param json The json object.
 * @param field The field name.
 * @param must_free have to free after use.
 * @return The json string of field value if exists, or NULL.
 */
NYRA_UTILS_API const char *nyra_json_to_string(nyra_json_t *json,
                                             const char *field,
                                             bool *must_free);

/**
 * @brief Get value of field from json object in string format, if the type
 *        of field is not string, dumps the value in string format.
 * @param json The json object.
 * @param field The field name.
 * @param must_free have to free after use.
 * @return The json string of field value if exists, or NULL.
 */
NYRA_UTILS_API nyra_json_t *nyra_json_from_string(const char *msg,
                                               nyra_error_t *err);

/**
 * @brief Destroy a json object
 *
 * @param json The json object
 */
NYRA_UTILS_API void nyra_json_destroy(nyra_json_t *json);

NYRA_UTILS_API bool nyra_json_is_object(nyra_json_t *json);

NYRA_UTILS_API bool nyra_json_is_array(nyra_json_t *json);

NYRA_UTILS_API bool nyra_json_is_string(nyra_json_t *json);

NYRA_UTILS_API bool nyra_json_is_integer(nyra_json_t *json);

NYRA_UTILS_API bool nyra_json_is_boolean(nyra_json_t *json);

NYRA_UTILS_API bool nyra_json_is_real(nyra_json_t *json);

NYRA_UTILS_API bool nyra_json_is_true(nyra_json_t *json);

NYRA_UTILS_API bool nyra_json_is_null(nyra_json_t *json);

NYRA_UTILS_API const char *nyra_json_peek_string_value(nyra_json_t *json);

NYRA_UTILS_API int64_t nyra_json_get_integer_value(nyra_json_t *json);

NYRA_UTILS_API bool nyra_json_get_boolean_value(nyra_json_t *json);

NYRA_UTILS_API double nyra_json_get_real_value(nyra_json_t *json);

NYRA_UTILS_API double nyra_json_get_number_value(nyra_json_t *json);

NYRA_UTILS_API nyra_json_t *nyra_json_create_object(void);

NYRA_UTILS_API nyra_json_t *nyra_json_create_array(void);

NYRA_UTILS_API nyra_json_t *nyra_json_create_string(const char *str);

NYRA_UTILS_API nyra_json_t *nyra_json_create_integer(int64_t value);

NYRA_UTILS_API nyra_json_t *nyra_json_create_real(double value);

NYRA_UTILS_API nyra_json_t *nyra_json_create_boolean(bool value);

NYRA_UTILS_API nyra_json_t *nyra_json_create_true(void);

NYRA_UTILS_API nyra_json_t *nyra_json_create_false(void);

NYRA_UTILS_API nyra_json_t *nyra_json_create_null(void);

NYRA_UTILS_API size_t nyra_json_array_get_size(nyra_json_t *json);

NYRA_UTILS_API nyra_json_t *nyra_json_array_peek_item(nyra_json_t *json,
                                                   size_t index);

NYRA_UTILS_API void nyra_json_object_update_missing(nyra_json_t *json,
                                                  nyra_json_t *other);

NYRA_UTILS_API const char *nyra_json_object_iter_key(void *iter);

NYRA_UTILS_API nyra_json_t *nyra_json_object_iter_value(void *iter);

NYRA_UTILS_API void *nyra_json_object_iter(nyra_json_t *json);

NYRA_UTILS_API void *nyra_json_object_iter_at(nyra_json_t *json, const char *key);

NYRA_UTILS_API void *nyra_json_object_key_to_iter(const char *key);

NYRA_UTILS_API void *nyra_json_object_iter_next(nyra_json_t *json, void *iter);

NYRA_UTILS_API nyra_json_t *nyra_json_incref(nyra_json_t *json);
