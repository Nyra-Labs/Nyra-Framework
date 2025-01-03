//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>

#include "nyra_utils/lib/json.h"

typedef struct nyra_value_t nyra_value_t;

NYRA_UTILS_API nyra_value_t *nyra_value_from_json(nyra_json_t *json);

NYRA_UTILS_API nyra_json_t *nyra_value_to_json(nyra_value_t *self);

NYRA_UTILS_API bool nyra_value_set_from_json(nyra_value_t *self, nyra_json_t *json);
