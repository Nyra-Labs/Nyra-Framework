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

#define NYRA_GO_NO_RESPONSE_HANDLER 0
#define NYRA_GO_NYRA_ENV_SIGNATURE 0xCCCC1DD4BB4CA743U

typedef struct nyra_env_t nyra_env_t;
typedef struct nyra_go_extension_t nyra_go_extension_t;
typedef struct nyra_go_metadata_t nyra_go_metadata_t;
typedef struct nyra_go_msg_t nyra_go_msg_t;
typedef struct nyra_go_nyra_env_t nyra_go_nyra_env_t;
typedef struct nyra_go_value_t nyra_go_value_t;

void nyra_go_nyra_env_on_configure_done(uintptr_t bridge_addr);

void nyra_go_nyra_env_on_init_done(uintptr_t bridge_addr);

void nyra_go_nyra_env_on_start_done(uintptr_t bridge_addr);

void nyra_go_nyra_env_on_stop_done(uintptr_t bridge_addr);

void nyra_go_nyra_env_on_deinit_done(uintptr_t bridge_addr);

void nyra_go_nyra_env_on_create_instance_done(uintptr_t bridge_addr,
                                            uintptr_t instance_bridge_addr,
                                            uintptr_t context_addr);

nyra_go_error_t nyra_go_nyra_env_return_result(uintptr_t bridge_addr,
                                            uintptr_t cmd_result_bridge_addr,
                                            uintptr_t cmd_bridge_addr,
                                            nyra_go_handle_t handler_id);

nyra_go_error_t nyra_go_nyra_env_return_result_directly(
    uintptr_t bridge_addr, uintptr_t cmd_result_bridge_addr,
    nyra_go_handle_t handler_id);

nyra_go_error_t nyra_go_nyra_env_send_cmd(uintptr_t bridge_addr,
                                       uintptr_t cmd_bridge_addr,
                                       nyra_go_handle_t handler_id, bool is_ex);

nyra_go_error_t nyra_go_nyra_env_send_data(uintptr_t bridge_addr,
                                        uintptr_t data_bridge_addr,
                                        nyra_go_handle_t handler_id);

nyra_go_error_t nyra_go_nyra_env_send_video_frame(
    uintptr_t bridge_addr, uintptr_t video_frame_bridge_addr,
    nyra_go_handle_t handler_id);

nyra_go_error_t nyra_go_nyra_env_send_audio_frame(
    uintptr_t bridge_addr, uintptr_t audio_frame_bridge_addr,
    nyra_go_handle_t handler_id);

bool nyra_go_nyra_env_addon_create_extension(uintptr_t bridge_addr,
                                           const char *addon_name,
                                           const char *instance_name,
                                           nyra_go_handle_t callback);

void nyra_go_nyra_env_addon_destroy_extension(uintptr_t bridge_addr,
                                            uintptr_t extension_bridge_addr,
                                            nyra_go_handle_t callback);

void nyra_go_nyra_env_finalize(uintptr_t bridge_addr);

const char *nyra_go_nyra_env_debug_info(uintptr_t bridge_addr);

// In general, there are two ways to get a property from a nyra_env_t instance.
//
// - One is getting property based on an explicit type, ex:
//   nyra_go_nyra_property_get_int8. But if the type is string or buffer, the
//   property size must be known first, in other words, we need to fall back to
//   the second way even through we know the property type. That's why we do not
//   provide a function such as `nyra_go_nyra_property_get_string`.
//
// - Another is the property type is unknown, or the property size must be known
//   first. In this case, the `nyra_go_nyra_property_get_type_and_size` function
//   will be called first. And as the nyra_value_t is cloned during
//   `nyra_go_nyra_property_get_type_and_size`, so next we can get the property
//   from the preflight nyra_value_t.

/**
 * @brief Get the type and size of a property of the nyra_env_t. This function is
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
 *
 * @param value_addr The output for the nyra_value_t* of the property.
 */
nyra_go_error_t nyra_go_nyra_env_get_property_type_and_size(
    uintptr_t bridge_addr, const void *path, int path_len, uint8_t *type,
    uintptr_t *size, uintptr_t *value_addr);

/**
 * @brief Get the value of a property as int8 from the nyra_env_t.
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
nyra_go_error_t nyra_go_nyra_env_get_property_int8(uintptr_t bridge_addr,
                                                const void *path, int path_len,
                                                int8_t *value);

nyra_go_error_t nyra_go_nyra_env_get_property_int16(uintptr_t bridge_addr,
                                                 const void *path, int path_len,
                                                 int16_t *value);

nyra_go_error_t nyra_go_nyra_env_get_property_int32(uintptr_t bridge_addr,
                                                 const void *path, int path_len,
                                                 int32_t *value);

nyra_go_error_t nyra_go_nyra_env_get_property_int64(uintptr_t bridge_addr,
                                                 const void *path, int path_len,
                                                 int64_t *value);

nyra_go_error_t nyra_go_nyra_env_get_property_uint8(uintptr_t bridge_addr,
                                                 const void *path, int path_len,
                                                 uint8_t *value);

nyra_go_error_t nyra_go_nyra_env_get_property_uint16(uintptr_t bridge_addr,
                                                  const void *path,
                                                  int path_len,
                                                  uint16_t *value);

nyra_go_error_t nyra_go_nyra_env_get_property_uint32(uintptr_t bridge_addr,
                                                  const void *path,
                                                  int path_len,
                                                  uint32_t *value);

nyra_go_error_t nyra_go_nyra_env_get_property_uint64(uintptr_t bridge_addr,
                                                  const void *path,
                                                  int path_len,
                                                  uint64_t *value);

nyra_go_error_t nyra_go_nyra_env_get_property_float32(uintptr_t bridge_addr,
                                                   const void *path,
                                                   int path_len, float *value);

nyra_go_error_t nyra_go_nyra_env_get_property_float64(uintptr_t bridge_addr,
                                                   const void *path,
                                                   int path_len, double *value);

nyra_go_error_t nyra_go_nyra_env_get_property_bool(uintptr_t bridge_addr,
                                                const void *path, int path_len,
                                                bool *value);

nyra_go_error_t nyra_go_nyra_env_get_property_ptr(uintptr_t bridge_addr,
                                               const void *path, int path_len,
                                               nyra_go_handle_t *value);

nyra_go_error_t nyra_go_nyra_env_set_property_bool(uintptr_t bridge_addr,
                                                const void *path, int path_len,
                                                bool value,
                                                uintptr_t callback_handle);

nyra_go_error_t nyra_go_nyra_env_set_property_int8(uintptr_t bridge_addr,
                                                const void *path, int path_len,
                                                int8_t value,
                                                uintptr_t callback_handle);

nyra_go_error_t nyra_go_nyra_env_set_property_int16(uintptr_t bridge_addr,
                                                 const void *path, int path_len,
                                                 int16_t value,
                                                 uintptr_t callback_handle);

nyra_go_error_t nyra_go_nyra_env_set_property_int32(uintptr_t bridge_addr,
                                                 const void *path, int path_len,
                                                 int32_t value,
                                                 uintptr_t callback_handle);

nyra_go_error_t nyra_go_nyra_env_set_property_int64(uintptr_t bridge_addr,
                                                 const void *path, int path_len,
                                                 int64_t value,
                                                 uintptr_t callback_handle);

nyra_go_error_t nyra_go_nyra_env_set_property_uint8(uintptr_t bridge_addr,
                                                 const void *path, int path_len,
                                                 uint8_t value,
                                                 uintptr_t callback_handle);

nyra_go_error_t nyra_go_nyra_env_set_property_uint16(uintptr_t bridge_addr,
                                                  const void *path,
                                                  int path_len, uint16_t value,
                                                  uintptr_t callback_handle);

nyra_go_error_t nyra_go_nyra_env_set_property_uint32(uintptr_t bridge_addr,
                                                  const void *path,
                                                  int path_len, uint32_t value,
                                                  uintptr_t callback_handle);

nyra_go_error_t nyra_go_nyra_env_set_property_uint64(uintptr_t bridge_addr,
                                                  const void *path,
                                                  int path_len, uint64_t value,
                                                  uintptr_t callback_handle);

nyra_go_error_t nyra_go_nyra_env_set_property_float32(uintptr_t bridge_addr,
                                                   const void *path,
                                                   int path_len, float value,
                                                   uintptr_t callback_handle);

nyra_go_error_t nyra_go_nyra_env_set_property_float64(uintptr_t bridge_addr,
                                                   const void *path,
                                                   int path_len, double value,
                                                   uintptr_t callback_handle);

nyra_go_error_t nyra_go_nyra_env_set_property_string(
    uintptr_t bridge_addr, const void *path, int path_len, const void *value,
    int value_len, uintptr_t callback_handle);

nyra_go_error_t nyra_go_nyra_env_set_property_buf(uintptr_t bridge_addr,
                                               const void *path, int path_len,
                                               void *value, int value_len,
                                               uintptr_t callback_handle);

nyra_go_error_t nyra_go_nyra_env_set_property_ptr(uintptr_t bridge_addr,
                                               const void *path, int path_len,
                                               nyra_go_handle_t value,
                                               uintptr_t callback_handle);

/**
 * @brief Get the json string and the size of the json string of a property.
 *
 * @param bridge_addr The bit pattern of the pointer to the struct
 * nyra_go_nyra_env_t.
 * @param json_str_len The output for the size of the json string.
 * @param json_str A double pointer to the json string.
 *
 * A GO slice will be created with a capacity of @a json_str_len in GO world,
 * and @a json_str will be copied to the slice and destroy using
 * nyra_go_copy_c_str_to_slice_and_free.
 */
nyra_go_error_t nyra_go_nyra_env_get_property_json_and_size(
    uintptr_t bridge_addr, const void *path, int path_len,
    uintptr_t *json_str_len, const char **json_str);

/**
 * @brief Parse @a json_str as a json object and set it as a property.
 *
 * @param json_str The pointer to the underlying array of the GO slice. The data
 * it points to must be a valid json data.
 * @param json_str_len The length of the underlying array of the GO slice.
 */
nyra_go_error_t nyra_go_nyra_env_set_property_json_bytes(
    uintptr_t bridge_addr, const void *path, int path_len, const void *json_str,
    int json_str_len, uintptr_t callback_handle);

nyra_go_error_t nyra_go_nyra_env_init_property_from_json_bytes(
    uintptr_t bridge_addr, const void *json_str, int json_str_len);

void nyra_go_nyra_env_log(uintptr_t bridge_addr, int level, const void *func_name,
                        int func_name_len, const void *file_name,
                        int file_name_len, int line_no, const void *msg,
                        int msg_len);