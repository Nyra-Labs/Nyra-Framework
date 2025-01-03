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

typedef struct nyra_env_tester_t nyra_env_tester_t;

NYRA_RUNTIME_API bool nyra_env_tester_on_start_done(nyra_env_tester_t *self,
                                                  nyra_error_t *err);

typedef void (*nyra_env_tester_cmd_result_handler_func_t)(
    nyra_env_tester_t *self, nyra_shared_ptr_t *cmd_result, void *user_data,
    nyra_error_t *error);

typedef void (*nyra_env_tester_error_handler_func_t)(nyra_env_tester_t *self,
                                                    void *user_data,
                                                    nyra_error_t *error);

NYRA_RUNTIME_API bool nyra_env_tester_send_cmd(
    nyra_env_tester_t *self, nyra_shared_ptr_t *cmd,
    nyra_env_tester_cmd_result_handler_func_t handler, void *user_data,
    nyra_error_t *error);

NYRA_RUNTIME_API bool nyra_env_tester_send_data(
    nyra_env_tester_t *self, nyra_shared_ptr_t *data,
    nyra_env_tester_error_handler_func_t handler, void *user_data,
    nyra_error_t *error);

NYRA_RUNTIME_API bool nyra_env_tester_send_audio_frame(
    nyra_env_tester_t *self, nyra_shared_ptr_t *audio_frame,
    nyra_env_tester_error_handler_func_t handler, void *user_data,
    nyra_error_t *error);

NYRA_RUNTIME_API bool nyra_env_tester_send_video_frame(
    nyra_env_tester_t *self, nyra_shared_ptr_t *video_frame,
    nyra_env_tester_error_handler_func_t handler, void *user_data,
    nyra_error_t *error);

NYRA_RUNTIME_API bool nyra_env_tester_stop_test(nyra_env_tester_t *self,
                                              nyra_error_t *error);
