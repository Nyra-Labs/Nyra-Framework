//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include "nyra_utils/lib/buf.h"
#include "nyra_utils/lib/string.h"

NYRA_UTILS_API bool nyra_base64_to_string(nyra_string_t *result, nyra_buf_t *buf);

NYRA_UTILS_API bool nyra_base64_from_string(nyra_string_t *str, nyra_buf_t *result);
