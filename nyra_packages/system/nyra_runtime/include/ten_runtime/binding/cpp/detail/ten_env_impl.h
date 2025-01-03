//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/binding/cpp/detail/addon.h"
#include "nyra_runtime/binding/cpp/detail/extension.h"
#include "nyra_runtime/binding/cpp/detail/nyra_env.h"
#include "nyra_utils/lang/cpp/lib/error.h"

namespace ten {

class nyra_env_t;
class extension_t;

inline bool nyra_env_t::on_create_instance_done(void *instance, void *context,
                                               error_t *err) {
  void *c_instance = nullptr;

  auto *cpp_context = reinterpret_cast<addon_context_t *>(context);
  NYRA_ASSERT(cpp_context, "Invalid argument.");

  switch (cpp_context->task) {
    case ADDON_TASK_CREATE_EXTENSION:
      c_instance = extension_internal_accessor_t::get_c_extension(
          static_cast<extension_t *>(instance));
      break;
    default:
      NYRA_ASSERT(0, "Should not happen.");
      break;
  }

  NYRA_ASSERT(c_instance, "Should not happen.");

  bool rc = nyra_env_on_create_instance_done(
      c_nyra_env, c_instance, cpp_context->c_context,
      err != nullptr ? err->get_c_error() : nullptr);

  delete cpp_context;

  return rc;
}

}  // namespace ten
