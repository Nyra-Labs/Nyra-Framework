//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include <stdbool.h>

typedef struct nyra_env_tester_t nyra_env_tester_t;
typedef struct nyra_env_tester_proxy_t nyra_env_tester_proxy_t;
typedef struct nyra_error_t nyra_error_t;

typedef void (*nyra_env_tester_proxy_notify_func_t)(
    nyra_env_tester_t *nyra_env_tester, void *user_data);

NYRA_RUNTIME_API nyra_env_tester_proxy_t *nyra_env_tester_proxy_create(
    nyra_env_tester_t *nyra_env_tester, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_tester_proxy_release(nyra_env_tester_proxy_t *self,
                                                  nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_tester_proxy_notify(
    nyra_env_tester_proxy_t *self,
    nyra_env_tester_proxy_notify_func_t notify_func, void *user_data,
    nyra_error_t *err);
