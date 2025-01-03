//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include "nyra_utils/lib/error.h"

typedef struct nyra_env_t nyra_env_t;
typedef struct nyra_metadata_info_t nyra_metadata_info_t;

NYRA_RUNTIME_API bool nyra_env_on_configure_done(nyra_env_t *self,
                                               nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_on_init_done(nyra_env_t *self, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_on_deinit_done(nyra_env_t *self, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_on_start_done(nyra_env_t *self, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_on_stop_done(nyra_env_t *self, nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_on_create_extensions_done(nyra_env_t *self,
                                                       nyra_list_t *extensions,
                                                       nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_on_destroy_extensions_done(nyra_env_t *self,
                                                        nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_on_create_instance_done(nyra_env_t *self,
                                                     void *instance,
                                                     void *context,
                                                     nyra_error_t *err);

NYRA_RUNTIME_API bool nyra_env_on_destroy_instance_done(nyra_env_t *self,
                                                      void *context,
                                                      nyra_error_t *err);
