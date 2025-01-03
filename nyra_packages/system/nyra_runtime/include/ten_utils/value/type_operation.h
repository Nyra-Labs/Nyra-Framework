//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include "nyra_utils/container/list.h"
#include "nyra_utils/lib/json.h"
#include "nyra_utils/value/type.h"

NYRA_UTILS_API NYRA_TYPE nyra_type_from_string(const char *type_str);

NYRA_UTILS_API const char *nyra_type_to_string(NYRA_TYPE type);

NYRA_UTILS_PRIVATE_API nyra_list_t nyra_type_from_json(nyra_json_t *json);

NYRA_UTILS_PRIVATE_API bool nyra_type_is_compatible(NYRA_TYPE actual,
                                                  NYRA_TYPE expected);
