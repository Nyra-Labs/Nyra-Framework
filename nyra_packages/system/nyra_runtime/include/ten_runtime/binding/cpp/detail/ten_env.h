//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <functional>
#include <memory>

#include "nyra_runtime/binding/common.h"
#include "nyra_runtime/binding/cpp/detail/msg/audio_frame.h"
#include "nyra_runtime/binding/cpp/detail/msg/cmd/cmd.h"
#include "nyra_runtime/binding/cpp/detail/msg/cmd_result.h"
#include "nyra_runtime/binding/cpp/detail/msg/data.h"
#include "nyra_runtime/binding/cpp/detail/msg/video_frame.h"
#include "nyra_runtime/common/errno.h"
#include "nyra_runtime/msg/cmd_result/cmd_result.h"
#include "nyra_runtime/ten.h"
#include "nyra_runtime/nyra_env/internal/metadata.h"
#include "nyra_runtime/nyra_env/internal/on_xxx_done.h"
#include "nyra_runtime/nyra_env/internal/return.h"
#include "nyra_runtime/nyra_env/nyra_env.h"
#include "nyra_utils/lang/cpp/lib/error.h"
#include "nyra_utils/lang/cpp/lib/value.h"
#include "nyra_utils/lib/buf.h"
#include "nyra_utils/lib/error.h"
#include "nyra_utils/log/log.h"
#include "nyra_utils/macro/check.h"
#include "nyra_utils/value/value.h"
#include "nyra_utils/value/value_json.h"

using nyra_env_t = struct nyra_env_t;

namespace ten {

class app_t;
class extension_t;
class extension_group_t;
class addon_t;
class extension_group_addon_t;
class extension_addon_t;
class nyra_env_t;
class nyra_env_proxy_t;
class nyra_env_internal_accessor_t;

using result_handler_func_t =
    std::function<void(nyra_env_t &, std::unique_ptr<cmd_result_t>, error_t *)>;

using error_handler_func_t = std::function<void(nyra_env_t &, error_t *)>;

class nyra_env_t {
 public:
  // @{
  nyra_env_t(const nyra_env_t &) = delete;
  nyra_env_t(nyra_env_t &&) = delete;
  nyra_env_t &operator=(const nyra_env_t &) = delete;
  nyra_env_t &operator=(const nyra_env_t &&) = delete;
  // @}

  bool send_cmd(std::unique_ptr<cmd_t> &&cmd,
                result_handler_func_t &&result_handler = nullptr,
                error_t *err = nullptr) {
    return send_cmd_internal(std::move(cmd), std::move(result_handler), false,
                             err);
  }

  bool send_cmd_ex(std::unique_ptr<cmd_t> &&cmd,
                   result_handler_func_t &&result_handler = nullptr,
                   error_t *err = nullptr) {
    return send_cmd_internal(std::move(cmd), std::move(result_handler), true,
                             err);
  }

  bool send_data(std::unique_ptr<data_t> &&data,
                 error_handler_func_t &&error_handler = nullptr,
                 error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env && data, "Should not happen.");

    if (!data) {
      NYRA_ASSERT(0, "Invalid argument.");
      return false;
    }

    if (data->get_underlying_msg() == nullptr) {
      if (err != nullptr && err->get_c_error() != nullptr) {
        nyra_error_set(err->get_c_error(), NYRA_ERRNO_INVALID_ARGUMENT,
                      "Invalid data.");
      }
      return false;
    }

    auto rc = false;

    if (error_handler == nullptr) {
      rc = nyra_env_send_data(c_nyra_env, data->get_underlying_msg(), nullptr,
                             nullptr,
                             err != nullptr ? err->get_c_error() : nullptr);
    } else {
      auto *error_handler_ptr =
          new error_handler_func_t(std::move(error_handler));

      rc = nyra_env_send_data(c_nyra_env, data->get_underlying_msg(),
                             proxy_handle_error, error_handler_ptr,
                             err != nullptr ? err->get_c_error() : nullptr);
      if (!rc) {
        delete error_handler_ptr;
      }
    }

    if (rc) {
      // Only when the data has been sent successfully, we should give back
      // the ownership of the data message to the NYRA runtime.
      auto *cpp_data_ptr = data.release();
      delete cpp_data_ptr;
    }

    return rc;
  }

  bool send_video_frame(std::unique_ptr<video_frame_t> &&frame,
                        error_handler_func_t &&error_handler = nullptr,
                        error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");

    if (!frame) {
      NYRA_ASSERT(0, "Invalid argument.");
      return false;
    }

    auto rc = false;

    if (error_handler == nullptr) {
      rc = nyra_env_send_video_frame(
          c_nyra_env, frame->get_underlying_msg(), nullptr, nullptr,
          err != nullptr ? err->get_c_error() : nullptr);
    } else {
      auto *error_handler_ptr =
          new error_handler_func_t(std::move(error_handler));

      rc = nyra_env_send_video_frame(
          c_nyra_env, frame->get_underlying_msg(), proxy_handle_error,
          error_handler_ptr, err != nullptr ? err->get_c_error() : nullptr);
      if (!rc) {
        delete error_handler_ptr;
      }
    }

    if (rc) {
      // Only when the message has been sent successfully, we should give back
      // the ownership of the message to the NYRA runtime.
      auto *cpp_frame_ptr = frame.release();
      delete cpp_frame_ptr;
    }

    return rc;
  }

  bool send_audio_frame(std::unique_ptr<audio_frame_t> &&frame,
                        error_handler_func_t &&error_handler = nullptr,
                        error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");

    if (!frame) {
      NYRA_ASSERT(0, "Invalid argument.");
      return false;
    }

    auto rc = false;

    if (error_handler == nullptr) {
      rc = nyra_env_send_audio_frame(
          c_nyra_env, frame->get_underlying_msg(), nullptr, nullptr,
          err != nullptr ? err->get_c_error() : nullptr);
    } else {
      auto *error_handler_ptr =
          new error_handler_func_t(std::move(error_handler));

      rc = nyra_env_send_audio_frame(
          c_nyra_env, frame->get_underlying_msg(), proxy_handle_error,
          error_handler_ptr, err != nullptr ? err->get_c_error() : nullptr);
      if (!rc) {
        delete error_handler_ptr;
      }
    }

    if (rc) {
      // Only when the message has been sent successfully, we should give back
      // the ownership of the message to the NYRA runtime.
      auto *cpp_frame_ptr = frame.release();
      delete cpp_frame_ptr;
    }

    return rc;
  }

  // If the 'cmd' has already been a command in the backward path, a extension
  // could use this API to return the 'cmd' further.
  bool return_result_directly(std::unique_ptr<cmd_result_t> &&cmd,
                              error_handler_func_t &&error_handler = nullptr,
                              error_t *err = nullptr) {
    if (!cmd) {
      NYRA_ASSERT(0, "Invalid argument.");
      return false;
    }

    bool rc = false;
    if (error_handler == nullptr) {
      rc = nyra_env_return_result_directly(
          c_nyra_env, cmd->get_underlying_msg(), nullptr, nullptr,
          err != nullptr ? err->get_c_error() : nullptr);
    } else {
      auto *error_handler_ptr =
          new error_handler_func_t(std::move(error_handler));

      rc = nyra_env_return_result_directly(
          c_nyra_env, cmd->get_underlying_msg(), proxy_handle_return_error,
          error_handler_ptr, err != nullptr ? err->get_c_error() : nullptr);
      if (!rc) {
        delete error_handler_ptr;
      }
    }

    if (rc) {
      // The 'cmd' has been returned, so we should release the ownership of
      // the C msg from the 'cmd'.
      auto *cpp_cmd_ptr = cmd.release();
      delete cpp_cmd_ptr;
    }

    return rc;
  }

  bool return_result(std::unique_ptr<cmd_result_t> &&cmd,
                     std::unique_ptr<cmd_t> &&target_cmd,
                     error_handler_func_t &&error_handler = nullptr,
                     error_t *err = nullptr) {
    if (!cmd) {
      NYRA_ASSERT(0, "Invalid argument.");
      return false;
    }
    if (!target_cmd) {
      NYRA_ASSERT(0, "Invalid argument.");
      return false;
    }

    bool rc = false;

    if (error_handler == nullptr) {
      rc = nyra_env_return_result(c_nyra_env, cmd->get_underlying_msg(),
                                 target_cmd->get_underlying_msg(), nullptr,
                                 nullptr,
                                 err != nullptr ? err->get_c_error() : nullptr);
    } else {
      auto *error_handler_ptr =
          new error_handler_func_t(std::move(error_handler));

      rc = nyra_env_return_result(c_nyra_env, cmd->get_underlying_msg(),
                                 target_cmd->get_underlying_msg(),
                                 proxy_handle_return_error, error_handler_ptr,
                                 err != nullptr ? err->get_c_error() : nullptr);
      if (!rc) {
        delete error_handler_ptr;
      }
    }

    if (rc) {
      if (cmd->is_final()) {
        // Only when is_final is true does the ownership of target_cmd
        // transfer. Otherwise, target_cmd remains with the extension,
        // allowing the extension to return more results.
        auto *cpp_target_cmd_ptr = target_cmd.release();
        delete cpp_target_cmd_ptr;
      }

      auto *cpp_cmd_ptr = cmd.release();
      delete cpp_cmd_ptr;
    }

    return rc;
  }

  bool is_property_exist(const char *path, error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");

    if ((path == nullptr) || (strlen(path) == 0)) {
      if (err != nullptr && err->get_c_error() != nullptr) {
        nyra_error_set(err->get_c_error(), NYRA_ERRNO_INVALID_ARGUMENT,
                      "path should not be empty.");
      }
      return false;
    }

    return nyra_env_is_property_exist(
        c_nyra_env, path, err != nullptr ? err->get_c_error() : nullptr);
  }

  bool init_property_from_json(const char *json_str, error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");

    if (json_str == nullptr) {
      NYRA_ASSERT(0, "Invalid argument.");
      return false;
    }

    return nyra_env_init_property_from_json(
        c_nyra_env, json_str, err != nullptr ? err->get_c_error() : nullptr);
  }

  std::string get_property_to_json(const char *path, error_t *err = nullptr) {
    std::string result;

    if ((path == nullptr) || (strlen(path) == 0)) {
      if (err != nullptr && err->get_c_error() != nullptr) {
        nyra_error_set(err->get_c_error(), NYRA_ERRNO_INVALID_ARGUMENT,
                      "path should not be empty.");
      }
      return result;
    }

    auto *value = peek_property_value(path, err);
    if (value == nullptr) {
      return result;
    }
    nyra_json_t *c_json = nyra_value_to_json(value);
    if (c_json == nullptr) {
      return result;
    }

    bool must_free = false;
    const char *json_str = nyra_json_to_string(c_json, nullptr, &must_free);
    NYRA_ASSERT(json_str, "Failed to convert a JSON to a string");

    result = json_str;

    nyra_json_destroy(c_json);
    if (must_free) {
      NYRA_FREE(json_str);
    }

    return result;
  }

  bool set_property_from_json(const char *path, const char *json_str,
                              error_t *err = nullptr) {
    nyra_json_t *c_json = nyra_json_from_string(
        json_str, err != nullptr ? err->get_c_error() : nullptr);
    if (c_json == nullptr) {
      return false;
    }

    nyra_value_t *value = nyra_value_from_json(c_json);
    nyra_json_destroy(c_json);

    return set_property_impl(path, value, err);
  }

  uint8_t get_property_uint8(const char *path, error_t *err = nullptr) {
    nyra_value_t *c_value = peek_property_value(path, err);
    if (c_value == nullptr) {
      return 0;
    }

    error_t cpp_err;
    auto result = nyra_value_get_uint8(c_value, cpp_err.get_c_error());
    if (!cpp_err.is_success()) {
      NYRA_LOGW("Failed to get property %s because of incorrect type.", path);
    }
    if (err != nullptr) {
      nyra_error_copy(err->get_c_error(), cpp_err.get_c_error());
    }

    return result;
  }

  uint16_t get_property_uint16(const char *path, error_t *err = nullptr) {
    nyra_value_t *c_value = peek_property_value(path, err);
    if (c_value == nullptr) {
      return 0;
    }

    error_t cpp_err;
    auto result = nyra_value_get_uint16(c_value, cpp_err.get_c_error());
    if (!cpp_err.is_success()) {
      NYRA_LOGW("Failed to get property %s because of incorrect type.", path);
    }
    if (err != nullptr) {
      nyra_error_copy(err->get_c_error(), cpp_err.get_c_error());
    }

    return result;
  }

  uint32_t get_property_uint32(const char *path, error_t *err = nullptr) {
    nyra_value_t *c_value = peek_property_value(path, err);
    if (c_value == nullptr) {
      return 0;
    }

    error_t cpp_err;
    auto result = nyra_value_get_uint32(c_value, cpp_err.get_c_error());
    if (!cpp_err.is_success()) {
      NYRA_LOGW("Failed to get property %s because of incorrect type.", path);
    }
    if (err != nullptr) {
      nyra_error_copy(err->get_c_error(), cpp_err.get_c_error());
    }

    return result;
  }

  uint64_t get_property_uint64(const char *path, error_t *err = nullptr) {
    nyra_value_t *c_value = peek_property_value(path, err);
    if (c_value == nullptr) {
      return 0;
    }

    error_t cpp_err;
    auto result = nyra_value_get_uint64(c_value, cpp_err.get_c_error());
    if (!cpp_err.is_success()) {
      NYRA_LOGW("Failed to get property %s because of incorrect type.", path);
    }
    if (err != nullptr) {
      nyra_error_copy(err->get_c_error(), cpp_err.get_c_error());
    }

    return result;
  }

  int8_t get_property_int8(const char *path, error_t *err = nullptr) {
    nyra_value_t *c_value = peek_property_value(path, err);
    if (c_value == nullptr) {
      return 0;
    }

    error_t cpp_err;
    auto result = nyra_value_get_int8(c_value, cpp_err.get_c_error());
    if (!cpp_err.is_success()) {
      NYRA_LOGW("Failed to get property %s because of incorrect type.", path);
    }
    if (err != nullptr) {
      nyra_error_copy(err->get_c_error(), cpp_err.get_c_error());
    }

    return result;
  }

  int16_t get_property_int16(const char *path, error_t *err = nullptr) {
    nyra_value_t *c_value = peek_property_value(path, err);
    if (c_value == nullptr) {
      return 0;
    }

    error_t cpp_err;
    auto result = nyra_value_get_int16(c_value, cpp_err.get_c_error());
    if (!cpp_err.is_success()) {
      NYRA_LOGW("Failed to get property %s because of incorrect type.", path);
    }
    if (err != nullptr) {
      nyra_error_copy(err->get_c_error(), cpp_err.get_c_error());
    }

    return result;
  }

  int32_t get_property_int32(const char *path, error_t *err = nullptr) {
    nyra_value_t *c_value = peek_property_value(path, err);
    if (c_value == nullptr) {
      return 0;
    }

    error_t cpp_err;
    auto result = nyra_value_get_int32(c_value, cpp_err.get_c_error());
    if (!cpp_err.is_success()) {
      NYRA_LOGW("Failed to get property %s because of incorrect type.", path);
    }
    if (err != nullptr) {
      nyra_error_copy(err->get_c_error(), cpp_err.get_c_error());
    }

    return result;
  }

  int64_t get_property_int64(const char *path, error_t *err = nullptr) {
    nyra_value_t *c_value = peek_property_value(path, err);
    if (c_value == nullptr) {
      return 0;
    }

    error_t cpp_err;
    auto result = nyra_value_get_int64(c_value, cpp_err.get_c_error());
    if (!cpp_err.is_success()) {
      NYRA_LOGW("Failed to get property %s because of incorrect type.", path);
    }
    if (err != nullptr) {
      nyra_error_copy(err->get_c_error(), cpp_err.get_c_error());
    }

    return result;
  }

  float get_property_float32(const char *path, error_t *err = nullptr) {
    nyra_value_t *c_value = peek_property_value(path, err);
    if (c_value == nullptr) {
      return 0.0F;
    }

    error_t cpp_err;
    auto result = nyra_value_get_float32(c_value, cpp_err.get_c_error());
    if (!cpp_err.is_success()) {
      NYRA_LOGW("Failed to get property %s because of incorrect type.", path);
    }
    if (err != nullptr) {
      nyra_error_copy(err->get_c_error(), cpp_err.get_c_error());
    }

    return result;
  }

  double get_property_float64(const char *path, error_t *err = nullptr) {
    nyra_value_t *c_value = peek_property_value(path, err);
    if (c_value == nullptr) {
      return 0.0F;
    }

    error_t cpp_err;
    auto result = nyra_value_get_float64(c_value, cpp_err.get_c_error());
    if (!cpp_err.is_success()) {
      NYRA_LOGW("Failed to get property %s because of incorrect type.", path);
    }
    if (err != nullptr) {
      nyra_error_copy(err->get_c_error(), cpp_err.get_c_error());
    }

    return result;
  }

  std::string get_property_string(const char *path, error_t *err = nullptr) {
    nyra_value_t *c_value = peek_property_value(path, err);
    if (c_value == nullptr) {
      return "";
    }

    error_t cpp_err;
    const auto *result = nyra_value_peek_raw_str(c_value, cpp_err.get_c_error());
    if (!cpp_err.is_success()) {
      NYRA_LOGW("Failed to get property %s because of incorrect type.", path);
    }
    if (err != nullptr) {
      nyra_error_copy(err->get_c_error(), cpp_err.get_c_error());
    }

    if (result != nullptr) {
      return result;
    } else {
      return "";
    }
  }

  void *get_property_ptr(const char *path, error_t *err = nullptr) {
    nyra_value_t *c_value = peek_property_value(path, err);
    if (c_value == nullptr) {
      return nullptr;
    }

    error_t cpp_err;
    auto *result = nyra_value_get_ptr(c_value, cpp_err.get_c_error());
    if (!cpp_err.is_success()) {
      NYRA_LOGW("Failed to get property %s because of incorrect type.", path);
    }
    if (err != nullptr) {
      nyra_error_copy(err->get_c_error(), cpp_err.get_c_error());
    }

    return result;
  }

  bool get_property_bool(const char *path, error_t *err = nullptr) {
    nyra_value_t *c_value = peek_property_value(path, err);
    if (c_value == nullptr) {
      return false;
    }

    error_t cpp_err;
    auto result = nyra_value_get_bool(c_value, cpp_err.get_c_error());
    if (!cpp_err.is_success()) {
      NYRA_LOGW("Failed to get property %s because of incorrect type.", path);
    }
    if (err != nullptr) {
      nyra_error_copy(err->get_c_error(), cpp_err.get_c_error());
    }

    return result;
  }

  bool set_property(const char *path, int8_t value, error_t *err = nullptr) {
    return set_property_impl(path, nyra_value_create_int8(value), err);
  }

  bool set_property(const char *path, int16_t value, error_t *err = nullptr) {
    return set_property_impl(path, nyra_value_create_int16(value), err);
  }

  bool set_property(const char *path, int32_t value, error_t *err = nullptr) {
    return set_property_impl(path, nyra_value_create_int32(value), err);
  }

  bool set_property(const char *path, int64_t value, error_t *err = nullptr) {
    return set_property_impl(path, nyra_value_create_int64(value), err);
  }

  bool set_property(const char *path, uint8_t value, error_t *err = nullptr) {
    return set_property_impl(path, nyra_value_create_uint8(value), err);
  }

  bool set_property(const char *path, uint16_t value, error_t *err = nullptr) {
    return set_property_impl(path, nyra_value_create_uint16(value), err);
  }

  bool set_property(const char *path, uint32_t value, error_t *err = nullptr) {
    return set_property_impl(path, nyra_value_create_uint32(value), err);
  }

  bool set_property(const char *path, uint64_t value, error_t *err = nullptr) {
    return set_property_impl(path, nyra_value_create_uint64(value), err);
  }

  bool set_property(const char *path, float value, error_t *err = nullptr) {
    return set_property_impl(path, nyra_value_create_float32(value), err);
  }

  bool set_property(const char *path, double value, error_t *err = nullptr) {
    return set_property_impl(path, nyra_value_create_float64(value), err);
  }

  bool set_property(const char *path, bool value, error_t *err = nullptr) {
    return set_property_impl(path, nyra_value_create_bool(value), err);
  }

  bool set_property(const char *path, void *value, error_t *err = nullptr) {
    return set_property_impl(
        path, nyra_value_create_ptr(value, nullptr, nullptr, nullptr), err);
  }

  bool set_property(const char *path, const char *value,
                    error_t *err = nullptr) {
    return set_property_impl(path, nyra_value_create_string(value), err);
  }

  // Convenient overloaded function for std::string type.
  bool set_property(const char *path, const std::string &value,
                    error_t *err = nullptr) {
    return set_property_impl(path, nyra_value_create_string(value.c_str()), err);
  }

  bool set_property(const char *path, const ten::buf_t &value,
                    error_t *err = nullptr) {
    nyra_buf_t buf =
        NYRA_BUF_STATIC_INIT_WITH_DATA_OWNED(value.data(), value.size());
    return set_property_impl(path, nyra_value_create_buf_with_move(buf), err);
  }

  bool on_configure_done(error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");

    bool rc = nyra_env_on_configure_done(
        c_nyra_env, err != nullptr ? err->get_c_error() : nullptr);

    return rc;
  }

  bool on_init_done(error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");

    bool rc = nyra_env_on_init_done(
        c_nyra_env, err != nullptr ? err->get_c_error() : nullptr);

    return rc;
  }

  bool on_deinit_done(error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");
    return nyra_env_on_deinit_done(
        c_nyra_env, err != nullptr ? err->get_c_error() : nullptr);
  }

  bool on_start_done(error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");
    return nyra_env_on_start_done(c_nyra_env,
                                 err != nullptr ? err->get_c_error() : nullptr);
  }

  bool on_stop_done(error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");
    return nyra_env_on_stop_done(c_nyra_env,
                                err != nullptr ? err->get_c_error() : nullptr);
  }

  bool on_create_instance_done(void *instance, void *context,
                               error_t *err = nullptr);

  bool on_destroy_instance_done(void *context, error_t *err = nullptr) {
    bool rc = nyra_env_on_destroy_instance_done(
        c_nyra_env, context, err != nullptr ? err->get_c_error() : nullptr);

    return rc;
  }

#define NYRA_ENV_LOG_VERBOSE(nyra_env, msg)                                      \
  do {                                                                         \
    (nyra_env).log(NYRA_LOG_LEVEL_VERBOSE, __func__, __FILE__, __LINE__, (msg)); \
  } while (0)

#define NYRA_ENV_LOG_DEBUG(nyra_env, msg)                                      \
  do {                                                                       \
    (nyra_env).log(NYRA_LOG_LEVEL_DEBUG, __func__, __FILE__, __LINE__, (msg)); \
  } while (0)

#define NYRA_ENV_LOG_INFO(nyra_env, msg)                                      \
  do {                                                                      \
    (nyra_env).log(NYRA_LOG_LEVEL_INFO, __func__, __FILE__, __LINE__, (msg)); \
  } while (0)

#define NYRA_ENV_LOG_WARN(nyra_env, msg)                                      \
  do {                                                                      \
    (nyra_env).log(NYRA_LOG_LEVEL_WARN, __func__, __FILE__, __LINE__, (msg)); \
  } while (0)

#define NYRA_ENV_LOG_ERROR(nyra_env, msg)                                      \
  do {                                                                       \
    (nyra_env).log(NYRA_LOG_LEVEL_ERROR, __func__, __FILE__, __LINE__, (msg)); \
  } while (0)

#define NYRA_ENV_LOG_FATAL(nyra_env, msg)                                      \
  do {                                                                       \
    (nyra_env).log(NYRA_LOG_LEVEL_FATAL, __func__, __FILE__, __LINE__, (msg)); \
  } while (0)

  void log(NYRA_LOG_LEVEL level, const char *func_name, const char *file_name,
           size_t line_no, const char *msg) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");
    nyra_env_log(c_nyra_env, level, func_name, file_name, line_no, msg);
  }

 private:
  friend class nyra_env_proxy_t;
  friend class app_t;
  friend class extension_t;
  friend class extension_group_t;
  friend class addon_t;
  friend class extension_group_addon_t;
  friend class extension_addon_t;
  friend class nyra_env_internal_accessor_t;

  ::nyra_env_t *c_nyra_env;

  explicit nyra_env_t(::nyra_env_t *c_nyra_env) : c_nyra_env(c_nyra_env) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");

    nyra_binding_handle_set_me_in_target_lang(
        reinterpret_cast<nyra_binding_handle_t *>(c_nyra_env),
        static_cast<void *>(this));
  }

  ~nyra_env_t() { NYRA_ASSERT(c_nyra_env, "Should not happen."); }

  ::nyra_env_t *get_c_nyra_env() { return c_nyra_env; }

  void *get_attached_target(error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");

    return nyra_binding_handle_get_me_in_target_lang(
        reinterpret_cast<nyra_binding_handle_t *>(
            nyra_env_get_attached_target(c_nyra_env)));
  }

  bool init_manifest_from_json(const char *json_str, error_t *err);

  static void proxy_handle_return_error(::nyra_env_t *nyra_env, void *user_data,
                                        ::nyra_error_t *err) {
    NYRA_ASSERT(nyra_env, "Should not happen.");

    auto *error_handler = static_cast<error_handler_func_t *>(user_data);
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

    if (err != nullptr) {
      error_t cpp_err(err, false);
      (*error_handler)(*cpp_nyra_env, &cpp_err);
    } else {
      (*error_handler)(*cpp_nyra_env, nullptr);
    }

    delete error_handler;
  }

  bool send_cmd_internal(std::unique_ptr<cmd_t> &&cmd,
                         result_handler_func_t &&result_handler = nullptr,
                         bool is_ex = false, error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");

    bool rc = false;

    if (!cmd) {
      NYRA_ASSERT(0, "Invalid argument.");
      return rc;
    }

    nyra_env_send_cmd_func_t send_cmd_func = nullptr;
    if (is_ex) {
      send_cmd_func = nyra_env_send_cmd_ex;
    } else {
      send_cmd_func = nyra_env_send_cmd;
    }

    if (result_handler == nullptr) {
      rc = send_cmd_func(c_nyra_env, cmd->get_underlying_msg(), nullptr, nullptr,
                         err != nullptr ? err->get_c_error() : nullptr);
    } else {
      auto *result_handler_ptr =
          new result_handler_func_t(std::move(result_handler));

      rc = send_cmd_func(c_nyra_env, cmd->get_underlying_msg(),
                         proxy_handle_result, result_handler_ptr,
                         err != nullptr ? err->get_c_error() : nullptr);
      if (!rc) {
        delete result_handler_ptr;
      }
    }

    if (rc) {
      // Only when the cmd has been sent successfully, we should give back the
      // ownership of the cmd to the NYRA runtime.
      auto *cpp_cmd_ptr = cmd.release();
      delete cpp_cmd_ptr;
    }

    return rc;
  }

  nyra_value_t *peek_property_value(const char *path, error_t *err) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");

    return nyra_env_peek_property(c_nyra_env, path,
                                 err != nullptr ? err->get_c_error() : nullptr);
  }

  /**
   * @note Note the move semantics of @a value. The @a value should not be
   * used after calling this function.
   */
  bool set_property_impl(const char *path, nyra_value_t *value, error_t *err) {
    NYRA_ASSERT(c_nyra_env, "Should not happen.");

    bool rc = nyra_env_set_property(
        c_nyra_env, path, value, err != nullptr ? err->get_c_error() : nullptr);

    if (!rc) {
      nyra_value_destroy(value);
    }
    return rc;
  }

  static void proxy_handle_result(::nyra_env_t *nyra_env,
                                  nyra_shared_ptr_t *c_cmd_result, void *cb_data,
                                  nyra_error_t *err) {
    auto *result_handler = static_cast<result_handler_func_t *>(cb_data);
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

    auto cmd_result = cmd_result_t::create(
        // Clone a C shared_ptr to be owned by the C++ instance.
        nyra_shared_ptr_clone(c_cmd_result));

    // After being processed by the `result_handler`, the `is_completed` value
    // of `cmd_result` may change. For example, if a command is passed between
    // two extensions within the same extension group (thread), the
    // `result_handler` in the source extension might directly invoke the
    // `on_cmd` logic of the destination extension. The logic within `on_cmd`
    // might then call `return_cmd`, which would cause the `is_completed` value
    // of the _same_ `cmd_result` to be modified. Therefore, before executing
    // the `result_handler`, the `is_completed` value needed for subsequent
    // decisions must be cached. After the `result_handler` has finished
    // executing, processing should be based on this cached value.
    bool is_completed = nyra_cmd_result_is_completed(c_cmd_result, nullptr);

    if (err != nullptr) {
      error_t cpp_err(err, false);
      (*result_handler)(*cpp_nyra_env, std::move(cmd_result), &cpp_err);
    } else {
      (*result_handler)(*cpp_nyra_env, std::move(cmd_result), nullptr);
    }

    if (is_completed) {
      // Only when is_final is true should the result handler be cleared.
      // Otherwise, since more result handlers are expected, the result
      // handler should not be cleared.
      delete result_handler;
    }
  }

  static void proxy_handle_error(::nyra_env_t *nyra_env,
                                 nyra_shared_ptr_t *c_cmd_result, void *cb_data,
                                 nyra_error_t *err) {
    NYRA_ASSERT(c_cmd_result == nullptr, "Should not happen.");

    auto *error_handler = static_cast<error_handler_func_t *>(cb_data);
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

    if (err == nullptr) {
      (*error_handler)(*cpp_nyra_env, nullptr);
    } else {
      error_t cpp_err(err, false);
      (*error_handler)(*cpp_nyra_env, &cpp_err);
    }

    // The error handler should be cleared.
    delete error_handler;
  };
};

}  // namespace ten