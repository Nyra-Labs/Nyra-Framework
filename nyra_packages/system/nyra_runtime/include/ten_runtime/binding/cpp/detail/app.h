//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <cstddef>
#include <string>

#include "nyra_runtime/app/app.h"
#include "nyra_runtime/binding/common.h"
#include "nyra_runtime/binding/cpp/detail/common.h"
#include "nyra_runtime/binding/cpp/detail/nyra_env.h"
#include "nyra_runtime/ten.h"
#include "nyra_utils/macro/check.h"

using nyra_app_t = struct nyra_app_t;

namespace ten {

class app_t {
 public:
  app_t()
      : c_app(nyra_app_create(cpp_app_on_configure_cb_wrapper,
                             cpp_app_on_init_cb_wrapper, nullptr, nullptr)),
        cpp_nyra_env(new nyra_env_t(nyra_app_get_nyra_env(c_app))) {
    NYRA_ASSERT(cpp_nyra_env, "Should not happen.");
    nyra_binding_handle_set_me_in_target_lang(
        reinterpret_cast<nyra_binding_handle_t *>(c_app),
        static_cast<void *>(this));
  }

  virtual ~app_t() {
    nyra_app_destroy(c_app);
    c_app = nullptr;

    NYRA_ASSERT(cpp_nyra_env, "Should not happen.");
    delete cpp_nyra_env;
  }

  // @{
  app_t(const app_t &) = delete;
  app_t(app_t &&) = delete;
  app_t &operator=(const app_t &) = delete;
  app_t &operator=(app_t &&) = delete;
  // @}

  bool run(bool run_in_background = false, error_t *err = nullptr) {
    if (c_app == nullptr) {
      return false;
    }

    return nyra_app_run(c_app, run_in_background,
                       err != nullptr ? err->get_c_error() : nullptr);
  }

  bool close(error_t *err = nullptr) {
    return nyra_app_close(c_app, err != nullptr ? err->get_c_error() : nullptr);
  }

  bool wait(error_t *err = nullptr) {
    return nyra_app_wait(c_app, err != nullptr ? err->get_c_error() : nullptr);
  }

 protected:
  virtual void on_configure(nyra_env_t &nyra_env) { nyra_env.on_configure_done(); }

  virtual void on_init(nyra_env_t &nyra_env) { nyra_env.on_init_done(); }

  virtual void on_deinit(nyra_env_t &nyra_env) { nyra_env.on_deinit_done(); }

 private:
  static void cpp_app_on_configure_cb_wrapper(nyra_app_t *app,
                                              ::nyra_env_t *nyra_env) {
    NYRA_ASSERT(app && nyra_app_check_integrity(app, true), "Should not happen.");
    NYRA_ASSERT(nyra_env && nyra_env_check_integrity(nyra_env, true),
               "Should not happen.");
    NYRA_ASSERT(nyra_app_get_nyra_env(app) == nyra_env, "Should not happen.");

    auto *cpp_app =
        static_cast<app_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(app)));
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

    cpp_app->on_configure_helper_for_cpp(*cpp_nyra_env);
  }

  void on_configure_helper_for_cpp(nyra_env_t &nyra_env) {
    // The NYRA runtime does not use C++ exceptions. The use of try/catch here is
    // merely to intercept any exceptions that might be thrown by the user's app
    // code. If exceptions are disabled during the compilation of the NYRA
    // runtime (i.e., with -fno-exceptions), it implies that the extensions used
    // will also not employ exceptions (otherwise it would be unreasonable). In
    // this case, the try/catch blocks become no-ops. Conversely, if exceptions
    // are enabled during compilation, then the try/catch here can intercept all
    // exceptions thrown by user code that are not already caught, serving as a
    // kind of fallback.
    try {
      on_configure(nyra_env);
    } catch (...) {
      NYRA_LOGW("Caught a exception of type '%s' in App on_configure().",
               curr_exception_type_name().c_str());
    }
  }

  static void cpp_app_on_init_cb_wrapper(nyra_app_t *app, ::nyra_env_t *nyra_env) {
    NYRA_ASSERT(app && nyra_app_check_integrity(app, true), "Should not happen.");
    NYRA_ASSERT(nyra_env && nyra_env_check_integrity(nyra_env, true),
               "Should not happen.");
    NYRA_ASSERT(nyra_app_get_nyra_env(app) == nyra_env, "Should not happen.");

    auto *cpp_app =
        static_cast<app_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(app)));
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

    cpp_app->on_init_helper_for_cpp(*cpp_nyra_env);
  }

  void on_init_helper_for_cpp(nyra_env_t &nyra_env) {
    // The NYRA runtime does not use C++ exceptions. The use of try/catch here is
    // merely to intercept any exceptions that might be thrown by the user's app
    // code. If exceptions are disabled during the compilation of the NYRA
    // runtime (i.e., with -fno-exceptions), it implies that the extensions used
    // will also not employ exceptions (otherwise it would be unreasonable). In
    // this case, the try/catch blocks become no-ops. Conversely, if exceptions
    // are enabled during compilation, then the try/catch here can intercept all
    // exceptions thrown by user code that are not already caught, serving as a
    // kind of fallback.
    try {
      on_init(nyra_env);
    } catch (...) {
      NYRA_LOGW("Caught a exception of type '%s' in App on_init().",
               curr_exception_type_name().c_str());
    }
  }

  static void cpp_app_on_close_cb_wrapper(nyra_app_t *app,
                                          ::nyra_env_t *nyra_env) {
    NYRA_ASSERT(app && nyra_app_check_integrity(app, true), "Should not happen.");
    NYRA_ASSERT(nyra_env && nyra_env_check_integrity(nyra_env, true),
               "Should not happen.");
    NYRA_ASSERT(nyra_app_get_nyra_env(app) == nyra_env, "Should not happen.");

    auto *cpp_app =
        static_cast<app_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(app)));
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

    cpp_app->on_deinit_helper_for_cpp(*cpp_nyra_env);
  }

  void on_deinit_helper_for_cpp(nyra_env_t &nyra_env) {
    // The NYRA runtime does not use C++ exceptions. The use of try/catch here is
    // merely to intercept any exceptions that might be thrown by the user's app
    // code. If exceptions are disabled during the compilation of the NYRA
    // runtime (i.e., with -fno-exceptions), it implies that the extensions used
    // will also not employ exceptions (otherwise it would be unreasonable). In
    // this case, the try/catch blocks become no-ops. Conversely, if exceptions
    // are enabled during compilation, then the try/catch here can intercept all
    // exceptions thrown by user code that are not already caught, serving as a
    // kind of fallback.
    try {
      on_deinit(nyra_env);
    } catch (...) {
      NYRA_LOGW("Caught a exception of type '%s' in App on_close().",
               curr_exception_type_name().c_str());
    }
  }

  ::nyra_app_t *c_app = nullptr;
  nyra_env_t *cpp_nyra_env;
};

}  // namespace ten
