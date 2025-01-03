//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <stdint.h>

#include "common.h"

nyra_go_error_t nyra_go_data_create(const void *msg_name, int msg_name_len,
                                  uintptr_t *bridge);

nyra_go_error_t nyra_go_data_alloc_buf(uintptr_t bridge_addr, int size);

nyra_go_error_t nyra_go_data_lock_buf(uintptr_t bridge_addr, uint8_t **buf_addr,
                                    uint64_t *buf_size);

nyra_go_error_t nyra_go_data_unlock_buf(uintptr_t bridge_addr,
                                      const void *buf_addr);

nyra_go_error_t nyra_go_data_get_buf(uintptr_t bridge_addr, const void *buf_addr,
                                   int buf_size);
