//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "common.h"

typedef struct nyra_go_msg_t nyra_go_msg_t;
typedef struct nyra_smart_ptr_t nyra_shared_ptr_t;
typedef struct nyra_go_value_t nyra_go_value_t;

/**
 * @brief Get the type and size of a property of the msg. This function is
 * called before getting property from the GO side, as the GO side needs to do
 * some preparation if the property is not a primitive type. Ex: the memory
 * should be allocated from the GO side, if the property is a buffer.
 *
 * @param path The underlying buffer of the GO string, which is passed with
 * unsafe.Pointer in GO world, so the type of @a path is void*, not char*. Only
 * the read operation is permitted. And the buffer is managed by GO, do not read
 * it after the blocking cgo call.
 *
 * @param path_len The length of the underlying buffer.
 *
 * @param type The output for the type of the property.
 *
 * @param size The output for the size of the property. The size is only used if
 * the property is not a primitive type.
 */
nyra_go_error_t nyra_go_msg_property_get_type_and_size(uintptr_t bridge_addr,
                                                     const void *path,
                                                     int path_len,
                                                     uint8_t *type,
                                                     uintptr_t *size);

/**
 * @brief Get the value of a property as int8 from the msg.
 *
 * @param path The underlying buffer of the GO string, which is passed with
 * unsafe.Pointer in GO world, so the type of @a path is void*, not char*. Only
 * the read operation is permitted. And the buffer is managed by GO, do not read
 * it after the blocking cgo call.
 *
 * @param path_len The length of the underlying buffer.
 *
 * @param value The output for the value of the property.
 */
nyra_go_error_t nyra_go_msg_property_get_int8(uintptr_t bridge_addr,
                                            const void *path, int path_len,
                                            int8_t *value);

nyra_go_error_t nyra_go_msg_property_get_int16(uintptr_t bridge_addr,
                                             const void *path, int path_len,
                                             int16_t *value);

nyra_go_error_t nyra_go_msg_property_get_int32(uintptr_t bridge_addr,
                                             const void *path, int path_len,
                                             int32_t *value);

nyra_go_error_t nyra_go_msg_property_get_int64(uintptr_t bridge_addr,
                                             const void *path, int path_len,
                                             int64_t *value);

nyra_go_error_t nyra_go_msg_property_get_uint8(uintptr_t bridge_addr,
                                             const void *path, int path_len,
                                             uint8_t *value);

nyra_go_error_t nyra_go_msg_property_get_uint16(uintptr_t bridge_addr,
                                              const void *path, int path_len,
                                              uint16_t *value);

nyra_go_error_t nyra_go_msg_property_get_uint32(uintptr_t bridge_addr,
                                              const void *path, int path_len,
                                              uint32_t *value);

nyra_go_error_t nyra_go_msg_property_get_uint64(uintptr_t bridge_addr,
                                              const void *path, int path_len,
                                              uint64_t *value);

nyra_go_error_t nyra_go_msg_property_get_float32(uintptr_t bridge_addr,
                                               const void *path, int path_len,
                                               float *value);

nyra_go_error_t nyra_go_msg_property_get_float64(uintptr_t bridge_addr,
                                               const void *path, int path_len,
                                               double *value);

nyra_go_error_t nyra_go_msg_property_get_bool(uintptr_t bridge_addr,
                                            const void *path, int path_len,
                                            bool *value);

/**
 * @brief Get the value of a property as string from the msg.
 *
 * @param path The underlying buffer of the GO string, which is passed with
 * unsafe.Pointer in GO world, so the type of @a path is void*, not char*. Only
 * the read operation is permitted. And the buffer is managed by GO, do not read
 * it after the blocking cgo call.
 *
 * @param path_len The length of the underlying buffer.
 *
 * @param value The output for the value of the property. The @a value is the
 * address of a slice which is allocated from GO side, and is passed as an
 * `unsafe.Pointer`, hence the type is `void*`. The length of the GO slice is
 * big enough to store the string value, as it is allocated based on the size
 * returned by nyra_go_msg_property_get_type_and_size. The string value will be
 * copied to @a value, then it's safe to create a GO string based on @a value in
 * GO side after this cgo call.
 */
nyra_go_error_t nyra_go_msg_property_get_string(uintptr_t bridge_addr,
                                              const void *path, int path_len,
                                              void *value);

/**
 * @brief Get the value of a property as buffer from the msg.
 *
 * @param path The underlying buffer of the GO string, which is passed with
 * unsafe.Pointer in GO world, so the type of @a path is void*, not char*. Only
 * the read operation is permitted. And the buffer is managed by GO, do not read
 * it after the blocking cgo call.
 *
 * @param path_len The length of the underlying buffer.
 *
 * @param value The output for the value of the property. The @a value is the
 * address of a slice which is allocated from GO side, and is passed as an
 * `unsafe.Pointer`, hence the type is `void*`. The length of the GO slice is
 * big enough to store the buffer value, as it is allocated based on the size
 * returned by nyra_go_msg_property_get_type_and_size. The buffer value will be
 * copied to @a value.
 */
nyra_go_error_t nyra_go_msg_property_get_buf(uintptr_t bridge_addr,
                                           const void *path, int path_len,
                                           void *value);

/**
 * @brief Get the value of a property as pointer from the msg.
 *
 * @param path The underlying buffer of the GO string, which is passed with
 * unsafe.Pointer in GO world, so the type of @a path is void*, not char*. Only
 * the read operation is permitted. And the buffer is managed by GO, do not read
 * it after the blocking cgo call.
 *
 * @param path_len The length of the underlying buffer.
 *
 * @param value The output for the value of the property.
 */
nyra_go_error_t nyra_go_msg_property_get_ptr(uintptr_t bridge_addr,
                                           const void *path, int path_len,
                                           nyra_go_handle_t *value);

nyra_go_error_t nyra_go_msg_property_set_bool(uintptr_t bridge_addr,
                                            const void *path, int path_len,
                                            bool value);

nyra_go_error_t nyra_go_msg_property_set_int8(uintptr_t bridge_addr,
                                            const void *path, int path_len,
                                            int8_t value);

nyra_go_error_t nyra_go_msg_property_set_int16(uintptr_t bridge_addr,
                                             const void *path, int path_len,
                                             int16_t value);

nyra_go_error_t nyra_go_msg_property_set_int32(uintptr_t bridge_addr,
                                             const void *path, int path_len,
                                             int32_t value);

nyra_go_error_t nyra_go_msg_property_set_int64(uintptr_t bridge_addr,
                                             const void *path, int path_len,
                                             int64_t value);

nyra_go_error_t nyra_go_msg_property_set_uint8(uintptr_t bridge_addr,
                                             const void *path, int path_len,
                                             uint8_t value);

nyra_go_error_t nyra_go_msg_property_set_uint16(uintptr_t bridge_addr,
                                              const void *path, int path_len,
                                              uint16_t value);

nyra_go_error_t nyra_go_msg_property_set_uint32(uintptr_t bridge_addr,
                                              const void *path, int path_len,
                                              uint32_t value);

nyra_go_error_t nyra_go_msg_property_set_uint64(uintptr_t bridge_addr,
                                              const void *path, int path_len,
                                              uint64_t value);

nyra_go_error_t nyra_go_msg_property_set_float32(uintptr_t bridge_addr,
                                               const void *path, int path_len,
                                               float value);

nyra_go_error_t nyra_go_msg_property_set_float64(uintptr_t bridge_addr,
                                               const void *path, int path_len,
                                               double value);

/**
 * @brief Set a GO string as a property of the msg.
 *
 * @param bridge_addr The bit pattern of the pointer to the struct nyra_go_msg_t.
 *
 * @param path The underlying buffer of the GO string, which is passed with
 * unsafe.Pointer in GO world, so the type of @a path is void*, not char*. Only
 * the read operation is permitted. And the buffer is managed by GO, do not read
 * it after the blocking cgo call.
 *
 * @param path_len The length of the underlying buffer of @a path.
 *
 * @param value Same as @a path, the underlying buffer of the GO string. Note
 * that, according to the api of `unsafe.StringData()`, the `value` is
 * unspecified, and may be NULL if the GO string is empty.
 *
 * @param value_len The length of the underlying buffer of @a value.
 */
nyra_go_error_t nyra_go_msg_property_set_string(uintptr_t bridge_addr,
                                              const void *path, int path_len,
                                              const void *value, int value_len);

/**
 * @brief Set a []byte as a property of the msg.
 *
 * @param bridge_addr The bit pattern of the pointer to the struct nyra_go_msg_t.
 *
 * @param path The underlying buffer of the GO string, which is passed with
 * unsafe.Pointer from GO world, so the type of @a path is void*, not char*.
 * Only the read operation is permitted. And the buffer is managed by GO, do not
 * read it after the blocking cgo call.
 *
 * @param path_len The length of the underlying buffer of @a path.
 *
 * @param value The address of the underlying array of the []byte, which is
 * passed with unsafe.Pointer from GO world, so the type of @a value is void*.
 * Only the read operation is permitted. And the buffer is managed by GO, do not
 * read it after the blocking cgo call. According to the document of
 * `unsafe.SliceData()`, the `value` will point to `&slice[:1][0]` if cap(slice)
 * > 0. As the function in GO world requires the `value_len` to be > 0, the
 * `value` is always valid.
 *
 * @param value_len The length of the underlying buffer of @a value.
 */
nyra_go_error_t nyra_go_msg_property_set_buf(uintptr_t bridge_addr,
                                           const void *path, int path_len,
                                           void *value, int value_len);

/**
 * @brief Set a GO Pointer as a property of the msg.
 *
 * @param bridge_addr The bit pattern of the pointer to the struct nyra_go_msg_t.
 *
 * @param path The underlying buffer of the GO string, which is passed with
 * unsafe.Pointer from GO world, so the type of @a path is void*, not char*.
 * Only the read operation is permitted. And the buffer is managed by GO, do not
 * read it after the blocking cgo call.
 *
 * @param path_len The length of the underlying buffer of @a path.
 *
 * @param value A GO handle pointing to the GO Pointer in the handle map in the
 * GO world.
 */
nyra_go_error_t nyra_go_msg_property_set_ptr(uintptr_t bridge_addr,
                                           const void *path, int path_len,
                                           nyra_go_handle_t value);

/**
 * @brief Get the json string and the size of the json string of a property.
 *
 * @param bridge_addr The bit pattern of the pointer to the struct nyra_go_msg_t.
 * @param json_str_len The output for the size of the json string.
 * @param json_str A double pointer to the json string.
 *
 * A GO slice will be created with a capacity of @a json_str_len in GO world,
 * and @a json_str will be copied to the slice and destroy using
 * nyra_go_copy_c_str_to_slice_and_free.
 */
nyra_go_error_t nyra_go_msg_property_get_json_and_size(uintptr_t bridge_addr,
                                                     const void *path,
                                                     int path_len,
                                                     uintptr_t *json_str_len,
                                                     const char **json_str);

/**
 * @brief Parse @a json_str as a json object and set it as a property.
 *
 * @param json_str The pointer to the underlying array of the GO slice. The data
 * it points to must be a valid json data.
 * @param json_str_len The length of the underlying array of the GO slice.
 */
nyra_go_error_t nyra_go_msg_property_set_json_bytes(uintptr_t bridge_addr,
                                                  const void *path,
                                                  int path_len,
                                                  const void *json_str,
                                                  int json_str_len);

/**
 * @brief Finalizes the Go message.
 *
 * @param bridge_addr The bit pattern of the pointer to the nyra_go_msg_t.
 * Reinterpret it as a pointer to the nyra_go_msg_t in the C world.
 */
void nyra_go_msg_finalize(uintptr_t bridge_addr);

nyra_go_error_t nyra_go_msg_get_name(uintptr_t bridge_addr, const char **name);
