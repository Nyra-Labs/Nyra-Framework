//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <stdbool.h>

#include "common.h"

typedef struct nyra_go_app_t nyra_go_app_t;

nyra_go_app_t *nyra_go_app_create(nyra_go_handle_t go_app_index);

void nyra_go_app_run(nyra_go_app_t *app_bridge, bool run_in_background);

void nyra_go_app_close(nyra_go_app_t *app);

void nyra_go_app_wait(nyra_go_app_t *app);

// Invoked when the Go app finalizes.
void nyra_go_app_finalize(nyra_go_app_t *self);
