//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include "nyra_runtime/common/status_code.h"
#include "nyra_utils/lib/error.h"
#include "nyra_utils/lib/smart_ptr.h"

typedef struct nyra_cmd_result_t nyra_cmd_result_t;

NYRA_RUNTIME_API nyra_shared_ptr_t *nyra_cmd_result_create(
    NYRA_STATUS_CODE status_code);

NYRA_RUNTIME_API nyra_shared_ptr_t *nyra_cmd_result_create_from_cmd(
    NYRA_STATUS_CODE status_code, nyra_shared_ptr_t *original_cmd);

NYRA_RUNTIME_API NYRA_STATUS_CODE
nyra_cmd_result_get_status_code(nyra_shared_ptr_t *self);

NYRA_RUNTIME_API bool nyra_cmd_result_is_final(nyra_shared_ptr_t *self,
                                             nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_cmd_result_is_completed(nyra_shared_ptr_t *self,
                                                 nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_cmd_result_set_final(nyra_shared_ptr_t *self,
                                              bool is_final, nyra_error_t *err);
