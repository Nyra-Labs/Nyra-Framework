//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include "nyra_utils/lib/smart_ptr.h"

typedef struct nyra_cmd_close_app_t nyra_cmd_close_app_t;

NYRA_RUNTIME_API nyra_shared_ptr_t *nyra_cmd_close_app_create(void);
