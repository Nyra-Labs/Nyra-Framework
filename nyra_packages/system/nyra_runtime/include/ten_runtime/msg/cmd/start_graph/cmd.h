//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include "nyra_utils/lib/error.h"
#include "nyra_utils/lib/smart_ptr.h"

typedef struct nyra_msg_t nyra_msg_t;
typedef struct nyra_cmd_start_graph_t nyra_cmd_start_graph_t;

NYRA_RUNTIME_API nyra_shared_ptr_t *nyra_cmd_start_graph_create(void);

NYRA_RUNTIME_API bool nyra_cmd_start_graph_set_predefined_graph_name(
    nyra_shared_ptr_t *self, const char *predefined_graph_name,
    nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_cmd_start_graph_set_long_running_mode(
    nyra_shared_ptr_t *self, bool long_running_mode, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_cmd_start_graph_set_graph_from_json_str(
    nyra_shared_ptr_t *self, const char *json_str, nyra_error_t *err);
