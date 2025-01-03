//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include <memory>

#include "nyra_runtime/binding/cpp/detail/msg/cmd/cmd.h"
#include "nyra_runtime/msg/cmd/stop_graph/cmd.h"
#include "nyra_utils/lib/smart_ptr.h"

namespace ten {

class extension_t;

class cmd_stop_graph_t : public cmd_t {
 private:
  friend extension_t;

  // Passkey Idiom.
  struct ctor_passkey_t {
   private:
    friend cmd_stop_graph_t;

    explicit ctor_passkey_t() = default;
  };

  explicit cmd_stop_graph_t(nyra_shared_ptr_t *cmd) : cmd_t(cmd) {}

 public:
  static std::unique_ptr<cmd_stop_graph_t> create(error_t *err = nullptr) {
    return std::make_unique<cmd_stop_graph_t>(ctor_passkey_t());
  }

  explicit cmd_stop_graph_t(ctor_passkey_t /*unused*/)
      : cmd_t(nyra_cmd_stop_graph_create()) {}
  ~cmd_stop_graph_t() override = default;

  // @{
  cmd_stop_graph_t(cmd_stop_graph_t &other) = delete;
  cmd_stop_graph_t(cmd_stop_graph_t &&other) = delete;
  cmd_stop_graph_t &operator=(const cmd_stop_graph_t &cmd) = delete;
  cmd_stop_graph_t &operator=(cmd_stop_graph_t &&cmd) = delete;
  // @}
};

}  // namespace ten