//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <string>
#include <utility>

#include "nyra_runtime/binding/common.h"
#include "nyra_runtime/binding/cpp/detail/common.h"
#include "nyra_runtime/binding/cpp/detail/msg/audio_frame.h"
#include "nyra_runtime/binding/cpp/detail/msg/cmd/cmd.h"
#include "nyra_runtime/binding/cpp/detail/msg/cmd/stop_graph.h"
#include "nyra_runtime/binding/cpp/detail/msg/data.h"
#include "nyra_runtime/binding/cpp/detail/msg/video_frame.h"
#include "nyra_runtime/binding/cpp/detail/nyra_env.h"
#include "nyra_runtime/extension/extension.h"
#include "nyra_runtime/msg/cmd/stop_graph/cmd.h"
#include "nyra_runtime/msg/msg.h"
#include "nyra_runtime/nyra_env/nyra_env.h"
#include "nyra_utils/lib/json.h"
#include "nyra_utils/lib/smart_ptr.h"
#include "nyra_utils/macro/check.h"

using nyra_json_t = ::nyra_json_t;
using nyra_env_t = struct nyra_env_t;
using nyra_extension_t = struct nyra_extension_t;

namespace ten {

class nyra_env_t;
class extension_group_t;

class extension_t {
 public:
  virtual ~extension_t() {
    NYRA_ASSERT(c_extension, "Should not happen.");
    nyra_extension_destroy(c_extension);

    NYRA_ASSERT(cpp_nyra_env, "Should not happen.");
    delete cpp_nyra_env;
  }

  // @{
  extension_t(const extension_t &) = delete;
  extension_t(extension_t &&) = delete;
  extension_t &operator=(const extension_t &) = delete;
  extension_t &operator=(const extension_t &&) = delete;
  // @}

 protected:
  explicit extension_t(const char *name)
      :  // In order to keep type safety in C++, the type of the 'ten'
         // parameters of these 4 functions are indeed 'ten::nyra_env_t'.
         // However, these callback functions are called from the C language
         // world, and in order to keep type safety in the C language world, it
         // better uses reinterpret_cast<> here, rather than change the type of
         // the second parameter of these callback functions from '::nyra_env_t
         // *' to 'void *'
        c_extension(::nyra_extension_create(
            name,
            reinterpret_cast<nyra_extension_on_configure_func_t>(
                &proxy_on_configure),
            reinterpret_cast<nyra_extension_on_init_func_t>(&proxy_on_init),
            reinterpret_cast<nyra_extension_on_start_func_t>(&proxy_on_start),
            reinterpret_cast<nyra_extension_on_stop_func_t>(&proxy_on_stop),
            reinterpret_cast<nyra_extension_on_deinit_func_t>(&proxy_on_deinit),
            reinterpret_cast<nyra_extension_on_cmd_func_t>(&proxy_on_cmd),
            reinterpret_cast<nyra_extension_on_data_func_t>(&proxy_on_data),
            reinterpret_cast<nyra_extension_on_audio_frame_func_t>(
                &proxy_on_audio_frame),
            reinterpret_cast<nyra_extension_on_video_frame_func_t>(
                &proxy_on_video_frame),
            nullptr)) {
    NYRA_ASSERT(c_extension, "Should not happen.");

    nyra_binding_handle_set_me_in_target_lang(
        reinterpret_cast<nyra_binding_handle_t *>(c_extension),
        static_cast<void *>(this));

    cpp_nyra_env = new nyra_env_t(nyra_extension_get_nyra_env(c_extension));
    NYRA_ASSERT(cpp_nyra_env, "Should not happen.");
  }

  virtual void on_configure(nyra_env_t &nyra_env) { nyra_env.on_configure_done(); }

  virtual void on_init(nyra_env_t &nyra_env) { nyra_env.on_init_done(); }

  virtual void on_start(nyra_env_t &nyra_env) { nyra_env.on_start_done(); }

  virtual void on_stop(nyra_env_t &nyra_env) { nyra_env.on_stop_done(); }

  virtual void on_deinit(nyra_env_t &nyra_env) { nyra_env.on_deinit_done(); }

  // Use std::shared_ptr to enable the C++ extension to save the received C++
  // messages and use it later. And use 'const shared_ptr&' to indicate that
  // the C++ extension "might" take a copy and share ownership of the cmd.

  virtual void on_cmd(nyra_env_t &nyra_env, std::unique_ptr<cmd_t> cmd) {
    auto cmd_result = ten::cmd_result_t::create(NYRA_STATUS_CODE_OK);
    cmd_result->set_property("detail", "default");
    nyra_env.return_result(std::move(cmd_result), std::move(cmd));
  }

  virtual void on_data(nyra_env_t &nyra_env, std::unique_ptr<data_t> data) {}

  virtual void on_audio_frame(nyra_env_t &nyra_env,
                              std::unique_ptr<audio_frame_t> frame) {}

  virtual void on_video_frame(nyra_env_t &nyra_env,
                              std::unique_ptr<video_frame_t> frame) {}

 private:
  friend class nyra_env_t;
  friend class extension_group_t;
  friend class extension_internal_accessor_t;

  ::nyra_extension_t *get_c_extension() const { return c_extension; }

  using cpp_extension_on_cmd_func_t =
      void (extension_t:: *)(nyra_env_t &, std::unique_ptr<cmd_t>);

  static void issue_stop_graph_cmd(nyra_env_t &nyra_env) {
    // Issue a 'close engine' command, and in order to gain the maximum
    // performance, we use C code directly here.
    nyra_shared_ptr_t *stop_graph_cmd = nyra_cmd_stop_graph_create();
    NYRA_ASSERT(stop_graph_cmd, "Should not happen.");

    nyra_msg_clear_and_set_dest(stop_graph_cmd, "localhost", nullptr, nullptr,
                               nullptr, nullptr);
    nyra_env_send_cmd(nyra_env.get_c_nyra_env(), stop_graph_cmd, nullptr, nullptr,
                     nullptr);
    nyra_shared_ptr_destroy(stop_graph_cmd);
  }

  static void proxy_on_configure(nyra_extension_t *extension,
                                 ::nyra_env_t *nyra_env) {
    NYRA_ASSERT(extension && nyra_env, "Should not happen.");

    auto *cpp_extension =
        static_cast<extension_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(extension)));
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

    cpp_extension->invoke_cpp_extension_on_configure(*cpp_nyra_env);
  }

  static void proxy_on_init(nyra_extension_t *extension, ::nyra_env_t *nyra_env) {
    NYRA_ASSERT(extension && nyra_env, "Should not happen.");

    auto *cpp_extension =
        static_cast<extension_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(extension)));
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

    cpp_extension->invoke_cpp_extension_on_init(*cpp_nyra_env);
  }

  static void proxy_on_start(nyra_extension_t *extension, ::nyra_env_t *nyra_env) {
    NYRA_ASSERT(extension && nyra_env, "Should not happen.");

    auto *cpp_extension =
        static_cast<extension_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(extension)));
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

    cpp_extension->invoke_cpp_extension_on_start(*cpp_nyra_env);
  }

  static void proxy_on_stop(nyra_extension_t *extension, ::nyra_env_t *nyra_env) {
    NYRA_ASSERT(extension && nyra_env, "Should not happen.");

    auto *cpp_extension =
        static_cast<extension_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(extension)));
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

    cpp_extension->invoke_cpp_extension_on_stop(*cpp_nyra_env);
  }

  static void proxy_on_deinit(nyra_extension_t *extension,
                              ::nyra_env_t *nyra_env) {
    NYRA_ASSERT(extension && nyra_env, "Should not happen.");

    auto *cpp_extension =
        static_cast<extension_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(extension)));
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

    cpp_extension->invoke_cpp_extension_on_deinit(*cpp_nyra_env);
  }

  static void proxy_on_cmd_internal(nyra_extension_t *extension,
                                    ::nyra_env_t *nyra_env, nyra_shared_ptr_t *cmd,
                                    cpp_extension_on_cmd_func_t on_cmd_func);

  static void proxy_on_cmd(nyra_extension_t *extension, ::nyra_env_t *nyra_env,
                           nyra_shared_ptr_t *cmd) {
    proxy_on_cmd_internal(extension, nyra_env, cmd, &extension_t::on_cmd);
  }

  static void proxy_on_data(nyra_extension_t *extension, ::nyra_env_t *nyra_env,
                            nyra_shared_ptr_t *data) {
    NYRA_ASSERT(extension && nyra_env, "Should not happen.");

    auto *cpp_extension =
        static_cast<extension_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(extension)));
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

    auto cpp_data_ptr = std::make_unique<data_t>(
        // Clone a C shared_ptr to be owned by the C++ instance.
        nyra_shared_ptr_clone(data));

    cpp_extension->invoke_cpp_extension_on_data(*cpp_nyra_env,
                                                std::move(cpp_data_ptr));
  }

  static void proxy_on_audio_frame(nyra_extension_t *extension,
                                   ::nyra_env_t *nyra_env,
                                   nyra_shared_ptr_t *frame) {
    NYRA_ASSERT(extension && nyra_env && frame, "Should not happen.");

    auto *cpp_extension =
        static_cast<extension_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(extension)));
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

    auto cpp_frame_ptr = std::make_unique<audio_frame_t>(
        // Clone a C shared_ptr to be owned by the C++ instance.
        nyra_shared_ptr_clone(frame));

    cpp_extension->invoke_cpp_extension_on_audio_frame(
        *cpp_nyra_env, std::move(cpp_frame_ptr));
  }

  static void proxy_on_video_frame(nyra_extension_t *extension,
                                   ::nyra_env_t *nyra_env,
                                   nyra_shared_ptr_t *frame) {
    NYRA_ASSERT(extension && nyra_env && frame, "Should not happen.");

    auto *cpp_extension =
        static_cast<extension_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(extension)));
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

    auto cpp_frame_ptr = std::make_unique<video_frame_t>(
        // Clone a C shared_ptr to be owned by the C++ instance.
        nyra_shared_ptr_clone(frame));

    cpp_extension->invoke_cpp_extension_on_video_frame(
        *cpp_nyra_env, std::move(cpp_frame_ptr));
  }

  void invoke_cpp_extension_on_configure(nyra_env_t &nyra_env) {
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
    } catch (std::exception &e) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception '") +
                                 e.what() + "' in on_configure()")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    } catch (...) {
      NYRA_ENV_LOG_WARN(nyra_env,
                       (std::string("Caught an exception of type '") +
                        curr_exception_type_name() + "in on_configure().")
                           .c_str());

      issue_stop_graph_cmd(nyra_env);
    }
  }

  void invoke_cpp_extension_on_init(nyra_env_t &nyra_env) {
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
    } catch (std::exception &e) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception '") +
                                 e.what() + "' in on_init()")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    } catch (...) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception of type '") +
                                 curr_exception_type_name() + "in on_init().")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    }
  }

  void invoke_cpp_extension_on_start(nyra_env_t &nyra_env) {
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
      on_start(nyra_env);
    } catch (std::exception &e) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception '") +
                                 e.what() + "' in on_start()")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    } catch (...) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception of type '") +
                                 curr_exception_type_name() + "in on_start().")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    }
  }

  void invoke_cpp_extension_on_stop(nyra_env_t &nyra_env) {
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
      on_stop(nyra_env);
    } catch (std::exception &e) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception '") +
                                 e.what() + "' in on_stop()")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    } catch (...) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception of type '") +
                                 curr_exception_type_name() + "in on_stop().")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    }
  }

  void invoke_cpp_extension_on_deinit(nyra_env_t &nyra_env) {
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
    } catch (std::exception &e) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception '") +
                                 e.what() + "' in on_deinit()")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    } catch (...) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception of type '") +
                                 curr_exception_type_name() + "in on_deinit().")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    }
  }

  void invoke_cpp_extension_on_cmd(nyra_env_t &nyra_env,
                                   std::unique_ptr<cmd_t> cmd,
                                   cpp_extension_on_cmd_func_t on_cmd_func) {
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
      (this->*on_cmd_func)(nyra_env, std::move(cmd));
    } catch (std::exception &e) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception '") +
                                 e.what() + "' in on_cmd()")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    } catch (...) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception of type '") +
                                 curr_exception_type_name() + "in on_cmd().")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    }
  }

  void invoke_cpp_extension_on_data(nyra_env_t &nyra_env,
                                    std::unique_ptr<data_t> data) {
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
      on_data(nyra_env, std::move(data));
    } catch (std::exception &e) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception '") +
                                 e.what() + "' in on_data()")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    } catch (...) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception of type '") +
                                 curr_exception_type_name() + "in on_data().")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    }
  }

  void invoke_cpp_extension_on_audio_frame(
      nyra_env_t &nyra_env, std::unique_ptr<audio_frame_t> frame) {
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
      on_audio_frame(nyra_env, std::move(frame));
    } catch (std::exception &e) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception '") +
                                 e.what() + "' in on_audio_frame()")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    } catch (...) {
      NYRA_ENV_LOG_WARN(nyra_env,
                       (std::string("Caught an exception of type '") +
                        curr_exception_type_name() + "in on_audio_frame().")
                           .c_str());

      issue_stop_graph_cmd(nyra_env);
    }
  }

  void invoke_cpp_extension_on_video_frame(
      nyra_env_t &nyra_env, std::unique_ptr<video_frame_t> frame) {
    // The NYRA runtime does not use C++ exceptions. The use of try/catch here is
    // merely to intercept any exceptions that might be thrown by the user's app
    // code. If exceptions are disabled during the compilation of the NYRAA
    // runtime (i.e., with -fno-exceptions), it implies that the extensions used
    // will also not employ exceptions (otherwise it would be unreasonable). In
    // this case, the try/catch blocks become no-ops. Conversely, if exceptions
    // are enabled during compilation, then the try/catch here can intercept all
    // exceptions thrown by user code that are not already caught, serving as a
    // kind of fallback.
    try {
      on_video_frame(nyra_env, std::move(frame));
    } catch (std::exception &e) {
      NYRA_ENV_LOG_WARN(nyra_env, (std::string("Caught an exception '") +
                                 e.what() + "' in on_video_frame()")
                                    .c_str());

      issue_stop_graph_cmd(nyra_env);
    } catch (...) {
      NYRA_ENV_LOG_WARN(nyra_env,
                       (std::string("Caught an exception of type '") +
                        curr_exception_type_name() + "in on_video_frame().")
                           .c_str());

      issue_stop_graph_cmd(nyra_env);
    }
  }

  ::nyra_extension_t *c_extension;
  nyra_env_t *cpp_nyra_env;
};

class extension_internal_accessor_t {
 public:
  static ::nyra_extension_t *get_c_extension(const extension_t *extension) {
    return extension->get_c_extension();
  }
};

}  // namespace ten
