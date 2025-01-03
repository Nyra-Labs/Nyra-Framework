//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

typedef struct nyra_protocol_t nyra_protocol_t;

NYRA_RUNTIME_API void nyra_protocol_close(nyra_protocol_t *self);
