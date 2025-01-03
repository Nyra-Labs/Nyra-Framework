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

NYRA_UTILS_API bool nyra_value_object_merge_with_move(nyra_value_t *dest,
                                                    nyra_value_t *src);

NYRA_UTILS_API bool nyra_value_object_merge_with_clone(nyra_value_t *dest,
                                                     nyra_value_t *src);

NYRA_UTILS_API bool nyra_value_object_merge_with_json(nyra_value_t *dest,
                                                    nyra_json_t *src);
