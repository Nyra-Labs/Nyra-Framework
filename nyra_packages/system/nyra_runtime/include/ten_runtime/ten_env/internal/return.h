//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include <stdbool.h>

#include "nyra_runtime/nyra_env/nyra_env.h"
#include "nyra_utils/lib/error.h"
#include "nyra_utils/lib/smart_ptr.h"

typedef void (*nyra_env_return_result_error_handler_func_t)(nyra_env_t *self,
                                                           void *user_data,
                                                           nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_return_result(
    nyra_env_t *self, nyra_shared_ptr_t *result, nyra_shared_ptr_t *target_cmd,
    nyra_env_return_result_error_handler_func_t error_handler,
    void *error_handler_user_data, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_return_result_directly(
    nyra_env_t *self, nyra_shared_ptr_t *cmd,
    nyra_env_return_result_error_handler_func_t error_handler,
    void *error_handler_user_data, nyra_error_t *err);
