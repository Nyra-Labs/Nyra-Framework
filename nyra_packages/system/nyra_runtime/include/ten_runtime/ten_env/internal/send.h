//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include <stdbool.h>

#include "nyra_utils/lib/error.h"
#include "nyra_utils/lib/smart_ptr.h"

typedef struct nyra_env_t nyra_env_t;
typedef struct nyra_extension_t nyra_extension_t;

typedef void (*nyra_env_msg_result_handler_func_t)(
    nyra_env_t *nyra_env, nyra_shared_ptr_t *cmd_result,
    void *cmd_result_handler_user_data, nyra_error_t *err);

typedef bool (*nyra_env_send_cmd_func_t)(
    nyra_env_t *self, nyra_shared_ptr_t *cmd,
    nyra_env_msg_result_handler_func_t result_handler,
    void *result_handler_user_data, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_send_cmd(
    nyra_env_t *self, nyra_shared_ptr_t *cmd,
    nyra_env_msg_result_handler_func_t result_handler,
    void *result_handler_user_data, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_send_cmd_ex(
    nyra_env_t *self, nyra_shared_ptr_t *cmd,
    nyra_env_msg_result_handler_func_t result_handler,
    void *result_handler_user_data, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_send_data(
    nyra_env_t *self, nyra_shared_ptr_t *data,
    nyra_env_msg_result_handler_func_t result_handler,
    void *result_handler_user_data, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_send_video_frame(
    nyra_env_t *self, nyra_shared_ptr_t *frame,
    nyra_env_msg_result_handler_func_t result_handler,
    void *result_handler_user_data, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_send_audio_frame(
    nyra_env_t *self, nyra_shared_ptr_t *frame,
    nyra_env_msg_result_handler_func_t result_handler,
    void *result_handler_user_data, nyra_error_t *err);
