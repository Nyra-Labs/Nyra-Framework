//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <cassert>
#include <cstddef>

#include "nyra_runtime/addon/addon.h"
#include "nyra_runtime/addon/extension/extension.h"
#include "nyra_runtime/binding/common.h"
#include "nyra_runtime/binding/cpp/detail/common.h"
#include "nyra_runtime/binding/cpp/detail/nyra_env.h"
#include "nyra_runtime/nyra_env/nyra_env.h"

namespace ten {

class addon_t {
 public:
  addon_t()
      : c_addon(nyra_addon_create(proxy_on_init, proxy_on_deinit,
                                 proxy_on_create_instance,
                                 proxy_on_destroy_instance, proxy_on_destroy)) {
    nyra_binding_handle_set_me_in_target_lang(
        reinterpret_cast<nyra_binding_handle_t *>(c_addon), this);
  }

  virtual ~addon_t() {
    nyra_addon_destroy(c_addon);
    c_addon = nullptr;

    NYRA_ASSERT(cpp_nyra_env, "Should not happen.");
    delete cpp_nyra_env;
  };

  // @{
  addon_t(const addon_t &) = delete;
  addon_t(addon_t &&) = delete;
  addon_t &operator=(const addon_t &) = delete;
  addon_t &operator=(const addon_t &&) = delete;
  // @}

 protected:
  virtual void on_init(nyra_env_t &nyra_env) { nyra_env.on_init_done(); }

  virtual void on_deinit(nyra_env_t &nyra_env) { nyra_env.on_deinit_done(); }

  virtual void on_create_instance(nyra_env_t &nyra_env, const char *name,
                                  void *context) = 0;
  virtual void on_destroy_instance(nyra_env_t &nyra_env, void *instance,
                                   void *context) = 0;

 private:
  nyra_addon_t *c_addon;
  nyra_env_t *cpp_nyra_env{};

  friend class addon_internal_accessor_t;

  ::nyra_addon_t *get_c_addon() const { return c_addon; }

  virtual void on_create_instance_impl(nyra_env_t &nyra_env, const char *name,
                                       void *context) = 0;

  void invoke_cpp_addon_on_init(nyra_env_t &nyra_env) {
    try {
      on_init(nyra_env);
    } catch (...) {
      NYRA_LOGW("Caught a exception of type '%s' in addon on_init().",
               curr_exception_type_name().c_str());
    }
  }

  void invoke_cpp_addon_on_deinit(nyra_env_t &nyra_env) {
    try {
      on_deinit(nyra_env);
    } catch (...) {
      NYRA_LOGD("Caught a exception '%s' in addon on_deinit().",
               curr_exception_type_name().c_str());
    }
  }

  void invoke_cpp_addon_on_create_instance(nyra_env_t &nyra_env, const char *name,
                                           void *context) {
    try {
      on_create_instance_impl(nyra_env, name, context);
    } catch (...) {
      NYRA_LOGD("Caught a exception '%s' in addon on_create_instance().",
               curr_exception_type_name().c_str());
    }
  }

  void invoke_cpp_addon_on_destroy_instance(nyra_env_t &nyra_env, void *instance,
                                            void *context) {
    try {
      on_destroy_instance(nyra_env, instance, context);
    } catch (...) {
      NYRA_LOGD("Caught a exception '%s' in addon on_destroy_instance().",
               curr_exception_type_name().c_str());
    }
  }

  static void proxy_on_init(nyra_addon_t *addon, ::nyra_env_t *nyra_env) {
    NYRA_ASSERT(addon && nyra_env, "Invalid argument.");

    auto *cpp_addon =
        static_cast<addon_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(addon)));
    NYRA_ASSERT(!nyra_binding_handle_get_me_in_target_lang(
                   reinterpret_cast<nyra_binding_handle_t *>(nyra_env)),
               "Should not happen.");

    auto *cpp_nyra_env = new nyra_env_t(nyra_env);
    NYRA_ASSERT(cpp_addon && cpp_nyra_env, "Should not happen.");

    // Remember it so that we can destroy it when C++ addon is destroyed.
    cpp_addon->cpp_nyra_env = cpp_nyra_env;

    cpp_addon->invoke_cpp_addon_on_init(*cpp_nyra_env);
  }

  static void proxy_on_deinit(nyra_addon_t *addon, ::nyra_env_t *nyra_env) {
    NYRA_ASSERT(addon && nyra_env, "Should not happen.");

    auto *cpp_addon =
        static_cast<addon_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(addon)));
    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));
    NYRA_ASSERT(cpp_addon && cpp_nyra_env, "Should not happen.");

    cpp_addon->invoke_cpp_addon_on_deinit(*cpp_nyra_env);
  }

  static void proxy_on_create_instance(nyra_addon_t *addon, ::nyra_env_t *nyra_env,
                                       const char *name, void *context) {
    NYRA_ASSERT(addon && nyra_env && name && strlen(name), "Invalid argument.");

    auto *cpp_addon =
        static_cast<addon_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(addon)));
    NYRA_ASSERT(cpp_addon, "Should not happen.");

    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));
    NYRA_ASSERT(cpp_nyra_env, "Should not happen.");

    cpp_addon->invoke_cpp_addon_on_create_instance(*cpp_nyra_env, name, context);
  }

  static void proxy_on_destroy_instance(nyra_addon_t *addon,
                                        ::nyra_env_t *nyra_env, void *instance,
                                        void *context) {
    NYRA_ASSERT(addon && nyra_env && instance, "Invalid argument.");

    auto *cpp_addon =
        static_cast<addon_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(addon)));

    auto *cpp_nyra_env =
        static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));
    NYRA_ASSERT(cpp_nyra_env, "Should not happen.");

    auto *cpp_instance = nyra_binding_handle_get_me_in_target_lang(
        static_cast<nyra_binding_handle_t *>(instance));
    NYRA_ASSERT(cpp_instance, "Should not happen.");

    cpp_addon->invoke_cpp_addon_on_destroy_instance(*cpp_nyra_env, cpp_instance,
                                                    context);
  }

  static void proxy_on_destroy(nyra_addon_t *addon) {
    NYRA_ASSERT(addon, "Invalid argument.");

    auto *cpp_addon =
        static_cast<addon_t *>(nyra_binding_handle_get_me_in_target_lang(
            reinterpret_cast<nyra_binding_handle_t *>(addon)));

    delete cpp_addon;
  }
};

namespace {

enum ADDON_TASK {
  ADDON_TASK_INVALID,

  ADDON_TASK_CREATE_EXTENSION,
  ADDON_TASK_CREATE_EXTENSION_GROUP,
};

struct addon_context_t {
  ADDON_TASK task;
  void *c_context;
};

}  // namespace

class addon_internal_accessor_t {
 public:
  static ::nyra_addon_t *get_c_addon(const addon_t *addon) {
    return addon->get_c_addon();
  }
};

class extension_addon_t : public addon_t {
 private:
  void on_create_instance_impl(nyra_env_t &nyra_env, const char *name,
                               void *context) override {
    auto *cpp_context = new addon_context_t();
    cpp_context->task = ADDON_TASK_CREATE_EXTENSION;
    cpp_context->c_context = context;

    on_create_instance(nyra_env, name, cpp_context);
  }
};

}  // namespace ten
