//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <memory>

#include "nyra_runtime/binding/common.h"
#include "nyra_runtime/binding/cpp/detail/msg/audio_frame.h"
#include "nyra_runtime/binding/cpp/detail/msg/cmd/cmd.h"
#include "nyra_runtime/binding/cpp/detail/msg/cmd_result.h"
#include "nyra_runtime/binding/cpp/detail/msg/data.h"
#include "nyra_runtime/binding/cpp/detail/msg/video_frame.h"
#include "nyra_runtime/test/env_tester.h"
#include "nyra_utils/lang/cpp/lib/error.h"

using nyra_extension_tester_t = struct nyra_extension_tester_t;
using nyra_env_tester_t = struct nyra_env_tester_t;

namespace ten {

class nyra_env_tester_t;
class extension_tester_t;

using nyra_env_tester_send_cmd_result_handler_func_t = std::function<void(
    nyra_env_tester_t &, std::unique_ptr<cmd_result_t>, error_t *)>;

class nyra_env_tester_t {
 public:
  // @{
  nyra_env_tester_t(const nyra_env_tester_t &) = delete;
  nyra_env_tester_t(nyra_env_tester_t &&) = delete;
  nyra_env_tester_t &operator=(const nyra_env_tester_t &) = delete;
  nyra_env_tester_t &operator=(const nyra_env_tester_t &&) = delete;
  // @}};

  bool on_start_done(error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env_tester, "Should not happen.");
    return nyra_env_tester_on_start_done(
        c_nyra_env_tester, err != nullptr ? err->get_c_error() : nullptr);
  }

  bool send_cmd(
      std::unique_ptr<cmd_t> &&cmd,
      nyra_env_tester_send_cmd_result_handler_func_t &&result_handler = nullptr,
      error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env_tester, "Should not happen.");

    bool rc = false;

    if (!cmd) {
      NYRA_ASSERT(0, "Invalid argument.");
      return rc;
    }

    if (result_handler == nullptr) {
      rc = nyra_env_tester_send_cmd(
          c_nyra_env_tester, cmd->get_underlying_msg(), nullptr, nullptr,
          err != nullptr ? err->get_c_error() : nullptr);
    } else {
      auto *result_handler_ptr =
          new nyra_env_tester_send_cmd_result_handler_func_t(
              std::move(result_handler));

      rc = nyra_env_tester_send_cmd(
          c_nyra_env_tester, cmd->get_underlying_msg(), proxy_handle_result,
          result_handler_ptr, err != nullptr ? err->get_c_error() : nullptr);
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

  bool send_data(std::unique_ptr<data_t> &&data, error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env_tester, "Should not happen.");

    bool rc = false;

    if (!data) {
      NYRA_ASSERT(0, "Invalid argument.");
      return rc;
    }

    rc = nyra_env_tester_send_data(
        c_nyra_env_tester, data->get_underlying_msg(), nullptr, nullptr,
        err != nullptr ? err->get_c_error() : nullptr);

    if (rc) {
      // Only when the data has been sent successfully, we should give back the
      // ownership of the data to the NYRA runtime.
      auto *cpp_data_ptr = data.release();
      delete cpp_data_ptr;
    }

    return rc;
  }

  bool send_audio_frame(std::unique_ptr<audio_frame_t> &&audio_frame,
                        error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env_tester, "Should not happen.");

    bool rc = false;

    if (!audio_frame) {
      NYRA_ASSERT(0, "Invalid argument.");
      return rc;
    }

    rc = nyra_env_tester_send_audio_frame(
        c_nyra_env_tester, audio_frame->get_underlying_msg(), nullptr, nullptr,
        err != nullptr ? err->get_c_error() : nullptr);

    if (rc) {
      // Only when the audio_frame has been sent successfully, we should give
      // back the ownership of the audio_frame to the NYRA runtime.
      auto *cpp_audio_frame_ptr = audio_frame.release();
      delete cpp_audio_frame_ptr;
    }

    return rc;
  }

  bool send_video_frame(std::unique_ptr<video_frame_t> &&video_frame,
                        error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env_tester, "Should not happen.");

    bool rc = false;

    if (!video_frame) {
      NYRA_ASSERT(0, "Invalid argument.");
      return rc;
    }

    rc = nyra_env_tester_send_video_frame(
        c_nyra_env_tester, video_frame->get_underlying_msg(), nullptr, nullptr,
        err != nullptr ? err->get_c_error() : nullptr);

    if (rc) {
      // Only when the video_frame has been sent successfully, we should give
      // back the ownership of the video_frame to the NYRA runtime.
      auto *cpp_video_frame_ptr = video_frame.release();
      delete cpp_video_frame_ptr;
    }

    return rc;
  }

  bool stop_test(error_t *err = nullptr) {
    NYRA_ASSERT(c_nyra_env_tester, "Should not happen.");
    return nyra_env_tester_stop_test(
        c_nyra_env_tester, err != nullptr ? err->get_c_error() : nullptr);
  }

 private:
  friend extension_tester_t;
  friend class nyra_env_tester_proxy_t;

  ::nyra_env_tester_t *c_nyra_env_tester;

  virtual ~nyra_env_tester_t() {
    NYRA_ASSERT(c_nyra_env_tester, "Should not happen.");
  }

  explicit nyra_env_tester_t(::nyra_env_tester_t *c_nyra_env_tester)
      : c_nyra_env_tester(c_nyra_env_tester) {
    NYRA_ASSERT(c_nyra_env_tester, "Should not happen.");

    nyra_binding_handle_set_me_in_target_lang(
        reinterpret_cast<nyra_binding_handle_t *>(c_nyra_env_tester),
        static_cast<void *>(this));
  }

  static void proxy_handle_result(::nyra_env_tester_t *c_nyra_env_tester,
                                  nyra_shared_ptr_t *c_cmd_result, void *cb_data,
                                  nyra_error_t *err) {
    auto *result_handler =
        static_cast<nyra_env_tester_send_cmd_result_handler_func_t *>(cb_data);
    auto *cpp_nyra_env_tester = static_cast<nyra_env_tester_t *>(
        nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(c_nyra_env_tester)));

    std::unique_ptr<cmd_result_t> cmd_result = nullptr;

    if (c_cmd_result != nullptr) {
      cmd_result = cmd_result_t::create(
          // Clone a C shared_ptr to be owned by the C++ instance.
          nyra_shared_ptr_clone(c_cmd_result));
    }

    if (err != nullptr) {
      error_t cpp_err(err, false);
      (*result_handler)(*cpp_nyra_env_tester, std::move(cmd_result), &cpp_err);
    } else {
      (*result_handler)(*cpp_nyra_env_tester, std::move(cmd_result), nullptr);
    }

    if (nyra_cmd_result_is_final(c_cmd_result, nullptr)) {
      // Only when is_final is true should the result handler be cleared.
      // Otherwise, since more result handlers are expected, the result
      // handler should not be cleared.
      delete result_handler;
    }
  }
};

}  // namespace ten
