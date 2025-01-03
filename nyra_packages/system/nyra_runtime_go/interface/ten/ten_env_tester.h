//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "common.h"

#define NYRA_GO_NYRA_ENV_TESTER_SIGNATURE 0x9159C741BA4A16D3U

void nyra_go_nyra_env_tester_finalize(uintptr_t bridge_addr);

void nyra_go_nyra_env_tester_on_start_done(uintptr_t bridge_addr);

nyra_go_error_t nyra_go_nyra_env_tester_send_cmd(uintptr_t bridge_addr,
                                              uintptr_t cmd_bridge_addr,
                                              nyra_go_handle_t handler_id);
