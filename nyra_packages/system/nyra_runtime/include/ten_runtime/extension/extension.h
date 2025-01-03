//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include <stdbool.h>

#include "nyra_utils/lib/smart_ptr.h"

typedef struct nyra_extension_t nyra_extension_t;
typedef struct nyra_env_t nyra_env_t;
typedef struct nyra_metadata_info_t nyra_metadata_info_t;

typedef void (*nyra_extension_on_configure_func_t)(nyra_extension_t *self,
                                                  nyra_env_t *nyra_env);

typedef void (*nyra_extension_on_init_func_t)(nyra_extension_t *self,
                                             nyra_env_t *nyra_env);

typedef void (*nyra_extension_on_start_func_t)(nyra_extension_t *self,
                                              nyra_env_t *nyra_env);

typedef void (*nyra_extension_on_stop_func_t)(nyra_extension_t *self,
                                             nyra_env_t *nyra_env);

typedef void (*nyra_extension_on_deinit_func_t)(nyra_extension_t *self,
                                               nyra_env_t *nyra_env);

typedef void (*nyra_extension_on_cmd_func_t)(nyra_extension_t *self,
                                            nyra_env_t *nyra_env,
                                            nyra_shared_ptr_t *cmd);

typedef void (*nyra_extension_on_data_func_t)(nyra_extension_t *self,
                                             nyra_env_t *nyra_env,
                                             nyra_shared_ptr_t *data);

typedef void (*nyra_extension_on_audio_frame_func_t)(nyra_extension_t *self,
                                                    nyra_env_t *nyra_env,
                                                    nyra_shared_ptr_t *frame);

typedef void (*nyra_extension_on_video_frame_func_t)(nyra_extension_t *self,
                                                    nyra_env_t *nyra_env,
                                                    nyra_shared_ptr_t *frame);

NYRA_RUNTIME_API bool nyra_extension_check_integrity(nyra_extension_t *self,
                                                   bool check_thread);

NYRA_RUNTIME_API nyra_extension_t *nyra_extension_create(
    const char *name, nyra_extension_on_configure_func_t on_configure,
    nyra_extension_on_init_func_t on_init,
    nyra_extension_on_start_func_t on_start,
    nyra_extension_on_stop_func_t on_stop,
    nyra_extension_on_deinit_func_t on_deinit,
    nyra_extension_on_cmd_func_t on_cmd, nyra_extension_on_data_func_t on_data,
    nyra_extension_on_audio_frame_func_t on_audio_frame,
    nyra_extension_on_video_frame_func_t on_video_frame, void *user_data);

NYRA_RUNTIME_API void nyra_extension_destroy(nyra_extension_t *self);

NYRA_RUNTIME_API nyra_env_t *nyra_extension_get_nyra_env(nyra_extension_t *self);
