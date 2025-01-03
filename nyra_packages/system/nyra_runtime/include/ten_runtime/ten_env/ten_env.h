//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include "nyra_runtime/common/errno.h"                  // IWYU pragma: keep
#include "nyra_runtime/nyra_env/internal/log.h"          // IWYU pragma: keep
#include "nyra_runtime/nyra_env/internal/metadata.h"     // IWYU pragma: keep
#include "nyra_runtime/nyra_env/internal/on_xxx_done.h"  // IWYU pragma: keep
#include "nyra_runtime/nyra_env/internal/return.h"       // IWYU pragma: keep
#include "nyra_runtime/nyra_env/internal/send.h"         // IWYU pragma: keep

typedef struct nyra_env_t nyra_env_t;
typedef struct nyra_extension_group_t nyra_extension_group_t;

typedef void (*nyra_env_addon_create_instance_done_cb_t)(nyra_env_t *nyra_env,
                                                        void *instance,
                                                        void *cb_data);

typedef void (*nyra_env_addon_destroy_instance_done_cb_t)(nyra_env_t *nyra_env,
                                                         void *cb_data);

typedef void (*nyra_env_is_cmd_connected_async_cb_t)(nyra_env_t *nyra_env,
                                                    bool result, void *cb_data,
                                                    nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_check_integrity(nyra_env_t *self,
                                             bool check_thread);

NYRA_RUNTIME_API bool nyra_env_is_cmd_connected(nyra_env_t *self,
                                              const char *cmd_name,
                                              nyra_error_t *err);

NYRA_RUNTIME_API void *nyra_env_get_attached_target(nyra_env_t *self);

NYRA_RUNTIME_API void nyra_env_destroy(nyra_env_t *self);
