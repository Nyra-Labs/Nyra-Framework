//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

typedef struct nyra_binding_handle_t nyra_binding_handle_t;

NYRA_RUNTIME_API void nyra_binding_handle_set_me_in_target_lang(
    nyra_binding_handle_t *self, void *me_in_target_lang);

NYRA_RUNTIME_API void *nyra_binding_handle_get_me_in_target_lang(
    nyra_binding_handle_t *self);
