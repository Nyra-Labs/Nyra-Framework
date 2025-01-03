//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <cassert>
#include <cstddef>

#include "nyra_runtime/addon/addon_manager.h"  // IWYU pragma: export

#define NYRA_CPP_REGISTER_ADDON_AS_EXNYRASION(NAME, CLASS)                         \
  class NAME##_default_extension_addon_t : public ten::extension_addon_t {       \
   public:                                                                       \
    void on_create_instance(ten::nyra_env_t &nyra_env, const char *name,           \
                            void *context) override {                            \
      auto *instance = new CLASS(name);                                          \
      nyra_env.on_create_instance_done(instance, context);                        \
    }                                                                            \
    void on_destroy_instance(ten::nyra_env_t &nyra_env, void *instance,            \
                             void *context) override {                           \
      delete static_cast<CLASS *>(instance);                                     \
      nyra_env.on_destroy_instance_done(context);                                 \
    }                                                                            \
  };                                                                             \
  static void ____nyra_addon_##NAME##_register_handler__(void *register_ctx) {    \
    auto *addon_instance = new NAME##_default_extension_addon_t();               \
    nyra_string_t *base_dir =                                                     \
        nyra_path_get_module_path(/* NOLINTNEXTLINE */                            \
                                 (void *)                                        \
                                     ____nyra_addon_##NAME##_register_handler__); \
    nyra_addon_register_extension(                                                \
        #NAME, nyra_string_get_raw_str(base_dir),                                 \
        ten::addon_internal_accessor_t::get_c_addon(addon_instance),             \
        register_ctx);                                                           \
    nyra_string_destroy(base_dir);                                                \
  }                                                                              \
  NYRA_CONSTRUCTOR(____nyra_addon_##NAME##_registrar____) {                        \
    /* Add addon registration function into addon manager. */                    \
    nyra_addon_manager_t *manager = nyra_addon_manager_get_instance();             \
    nyra_addon_manager_add_addon(manager, #NAME,                                  \
                                ____nyra_addon_##NAME##_register_handler__);      \
  }\
