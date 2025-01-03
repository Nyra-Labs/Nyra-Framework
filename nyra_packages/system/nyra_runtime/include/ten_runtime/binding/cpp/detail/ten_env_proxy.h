//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/binding/cpp/detail/nyra_env.h"
#include "nyra_runtime/nyra_env_proxy/nyra_env_proxy.h"

using nyra_extension_t = struct nyra_extension_t;
using nyra_env_proxy_t = struct nyra_env_proxy_t;
using nyra_env_t = struct nyra_env_t;

namespace ten {

class extension_t;
class extension_group_t;
class app_t;

namespace {

using notify_std_func_t = std::function<void(nyra_env_t &)>;
using notify_std_with_user_data_func_t =
    std::function<void(nyra_env_t &, void *user_data)>;

struct proxy_notify_info_t {
  explicit proxy_notify_info_t(notify_std_func_t &&func)
      : notify_std_func(std::move(func)) {}
  explicit proxy_notify_info_t(notify_std_with_user_data_func_t &&func,
                               void *user_data)
      : notify_std_with_user_data_func(std::move(func)), user_data(user_data) {}

  ~proxy_notify_info_t() = default;

  // @{
  proxy_notify_info_t(const proxy_notify_info_t &) = delete;
  proxy_notify_info_t &operator=(const proxy_notify_info_t &) = delete;
  proxy_notify_info_t(proxy_notify_info_t &&) = delete;
  proxy_notify_info_t &operator=(proxy_notify_info_t &&) = delete;
  // @}

  notify_std_func_t notify_std_func;

  notify_std_with_user_data_func_t notify_std_with_user_data_func;
  void *user_data{};
};

inline void proxy_notify(::nyra_env_t *nyra_env, void *data = nullptr) {
  NYRA_ASSERT(data, "Invalid argument.");

  auto *info = static_cast<proxy_notify_info_t *>(data);
  auto *cpp_nyra_env =
      static_cast<nyra_env_t *>(nyra_binding_handle_get_me_in_target_lang(
          reinterpret_cast<nyra_binding_handle_t *>(nyra_env)));

  if (info->notify_std_func != nullptr) {
    auto func = info->notify_std_func;
    func(*cpp_nyra_env);
  } else if (info->notify_std_with_user_data_func != nullptr) {
    auto func = info->notify_std_with_user_data_func;
    func(*cpp_nyra_env, info->user_data);
  }

  delete info;
}

}  // namespace

class nyra_env_proxy_t {
 private:
  // Passkey Idiom.
  struct ctor_passkey_t {
   private:
    friend nyra_env_proxy_t;

    explicit ctor_passkey_t() = default;
  };

 public:
  static nyra_env_proxy_t *create(nyra_env_t &nyra_env, error_t *err = nullptr) {
    return new nyra_env_proxy_t(nyra_env, ctor_passkey_t());
  }

  explicit nyra_env_proxy_t(nyra_env_t &nyra_env, ctor_passkey_t /*unused*/)
      : c_nyra_env_proxy(nyra_env_proxy_create(nyra_env.c_nyra_env, 1, nullptr)) {}

  ~nyra_env_proxy_t() {
    if (c_nyra_env_proxy == nullptr) {
      NYRA_ASSERT(0, "Invalid argument.");
    }

    bool rc = nyra_env_proxy_release(c_nyra_env_proxy, nullptr);
    NYRA_ASSERT(rc, "Should not happen.");
  };

  // @{
  nyra_env_proxy_t(nyra_env_proxy_t &other) = delete;
  nyra_env_proxy_t(nyra_env_proxy_t &&other) = delete;
  nyra_env_proxy_t &operator=(const nyra_env_proxy_t &other) = delete;
  nyra_env_proxy_t &operator=(nyra_env_proxy_t &&other) = delete;
  // @}

  bool acquire_lock_mode(error_t *err = nullptr) {
    if (c_nyra_env_proxy == nullptr) {
      NYRA_ASSERT(0, "Invalid argument.");
      return false;
    }

    return nyra_env_proxy_acquire_lock_mode(
        c_nyra_env_proxy, err != nullptr ? err->get_c_error() : nullptr);
  }

  bool release_lock_mode(error_t *err = nullptr) {
    if (c_nyra_env_proxy == nullptr) {
      NYRA_ASSERT(0, "Invalid argument.");
      return false;
    }

    return nyra_env_proxy_release_lock_mode(
        c_nyra_env_proxy, err != nullptr ? err->get_c_error() : nullptr);
  }

  bool notify(notify_std_func_t &&notify_func, bool sync = false,
              error_t *err = nullptr) {
    auto *info = new proxy_notify_info_t(std::move(notify_func));

    auto rc =
        nyra_env_proxy_notify(c_nyra_env_proxy, proxy_notify, info, sync,
                             err != nullptr ? err->get_c_error() : nullptr);
    if (!rc) {
      delete info;
    }

    return rc;
  }

  bool notify(notify_std_with_user_data_func_t &&notify_func, void *user_data,
              bool sync = false, error_t *err = nullptr) {
    auto *info = new proxy_notify_info_t(std::move(notify_func), user_data);

    auto rc =
        nyra_env_proxy_notify(c_nyra_env_proxy, proxy_notify, info, sync,
                             err != nullptr ? err->get_c_error() : nullptr);
    if (!rc) {
      delete info;
    }

    return rc;
  }

 private:
  ::nyra_env_proxy_t *c_nyra_env_proxy;

  // We do not provide the following API. If having similar needs, it can be
  // achieved by creating a new nyra_env_proxy.
  //
  // bool acquire(error_t *err = nullptr) {
  //   if (c_nyra_env_proxy == nullptr) {
  //     NYRA_ASSERT(0, "Invalid argument.");
  //     return false;
  //   }
  //   return nyra_proxy_acquire(
  //       c_nyra_env_proxy,
  //       err != nullptr ? err->get_c_error() : nullptr);
  // }
  //
  // bool release(error_t *err = nullptr) {
  //   if (c_nyra_env_proxy == nullptr) {
  //     NYRA_ASSERT(0, "Invalid argument.");
  //     return false;
  //   }
  //   bool rc = nyra_proxy_release(
  //       c_nyra_env_proxy,
  //       err != nullptr ? err->get_c_error() : nullptr);
  //   NYRA_ASSERT(rc, "Should not happen.");
  //   return rc;
  // }
};

}  // namespace ten
