//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdint.h>

typedef int64_t nyra_pid_t;

/**
 * @brief Get process id.
 */
NYRA_UTILS_API nyra_pid_t nyra_task_get_id();
