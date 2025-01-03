//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdint.h>

typedef uint64_t nyra_signature_t;

NYRA_UTILS_API void nyra_signature_set(nyra_signature_t *signature,
                                     nyra_signature_t value);

NYRA_UTILS_API nyra_signature_t
nyra_signature_get(const nyra_signature_t *signature);
