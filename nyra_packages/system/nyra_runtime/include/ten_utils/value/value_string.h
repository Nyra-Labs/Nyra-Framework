//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>

#include "nyra_utils/lib/string.h"
#include "nyra_utils/value/value_kv.h"

NYRA_UTILS_API bool nyra_value_to_string(nyra_value_t *self, nyra_string_t *str,
                                       nyra_error_t *err);

NYRA_UTILS_API nyra_value_t *nyra_value_from_type_and_string(NYRA_TYPE type,
                                                          const char *str,
                                                          nyra_error_t *err);
