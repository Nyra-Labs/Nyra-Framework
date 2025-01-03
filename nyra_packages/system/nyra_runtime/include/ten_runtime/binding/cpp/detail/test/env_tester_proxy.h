
//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <functional>

#include "nyra_runtime/binding/cpp/detail/test/env_tester.h"
#include "nyra_runtime/test/env_tester_proxy.h"

using nyra_env_tester_t = struct nyra_env_tester_t;
using nyra_env_tester_proxy_t = struct nyra_env_tester_proxy_t;

namespace ten {

namespace {

using tester_notify_std_func_t = std::function<void(nyra_env_tester_t &)>;

struct tester_proxy_notify_info_t {
  explicit tester_proxy_notify_info_t(tester_notify_std_func_t &&func)
      : notify_std_func(std::move(func)) {}

  ~tester_proxy_notify_info_t() = default;

  // @{
  tester_proxy_notify_info_t(const tester_proxy_notify_info_t &) = delete;
  tester_proxy_notify_info_t &operator=(const tester_proxy_notify_info_t &) =
      delete;
  tester_proxy_notify_info_t(tester_proxy_notify_info_t &&) = delete;
  tester_proxy_notify_info_t &operator=(tester_proxy_notify_info_t &&) = delete;
  // @}

  tester_notify_std_func_t notify_std_func;
};

inline void proxy_notify(::nyra_env_tester_t *nyra_env, void *data = nullptr) {
  NYRA_ASSERT(data, "Invalid argument.");

  auto *info = static_cast<tester_proxy_notify_info_t *>(data);
  auto *cpp_nyra_env =
      static_cast<nyra_env_tester_t *>(nyra_binding_handle_get_me_in_target_lang(
          reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

  if (info->notify_std_func != nullptr) {
    auto func = info->notify_std_func;
    func(*cpp_nyra_env);
  }

  delete info;
}

}  // namespace

class nyra_env_tester_proxy_t {
 private:
  // Passkey Idiom.
  struct ctor_passkey_t {
   private:
    friend nyra_env_tester_proxy_t;

    explicit ctor_passkey_t() = default;
  };

 public:
  // @{
  nyra_env_tester_proxy_t(const nyra_env_tester_proxy_t &) = delete;
  nyra_env_tester_proxy_t(nyra_env_tester_proxy_t &&) = delete;
  nyra_env_tester_proxy_t &operator=(const nyra_env_tester_proxy_t &) = delete;
  nyra_env_tester_proxy_t &operator=(const nyra_env_tester_proxy_t &&) = delete;
  // @{

  static nyra_env_tester_proxy_t *create(nyra_env_tester_t &nyra_env_tester,
                                        error_t *err = nullptr) {
    return new nyra_env_tester_proxy_t(nyra_env_tester, ctor_passkey_t());
  }

  explicit nyra_env_tester_proxy_t(nyra_env_tester_t &nyra_env_tester,
                                  ctor_passkey_t /*unused*/)
      : c_nyra_env_tester_proxy(nyra_env_tester_proxy_create(
            nyra_env_tester.c_nyra_env_tester, nullptr)) {}

  ~nyra_env_tester_proxy_t() {
    if (c_nyra_env_tester_proxy == nullptr) {
      NYRA_ASSERT(0, "Invalid argument.");
    }

    bool rc = nyra_env_tester_proxy_release(c_nyra_env_tester_proxy, nullptr);
    NYRA_ASSERT(rc, "Should not happen.");

    c_nyra_env_tester_proxy = nullptr;
  };

  bool notify(tester_notify_std_func_t &&notify_func, error_t *err = nullptr) {
    if (c_nyra_env_tester_proxy == nullptr) {
      NYRA_ASSERT(0, "Invalid argument.");
      return false;
    }

    auto *info = new tester_proxy_notify_info_t(std::move(notify_func));

    auto rc = nyra_env_tester_proxy_notify(
        c_nyra_env_tester_proxy, proxy_notify, info,
        err != nullptr ? err->get_c_error() : nullptr);
    if (!rc) {
      delete info;
    }

    return rc;
  }

 private:
  ::nyra_env_tester_proxy_t *c_nyra_env_tester_proxy;
};
}  // namespace ten