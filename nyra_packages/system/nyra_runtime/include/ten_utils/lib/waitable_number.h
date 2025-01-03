//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include "stdint.h"

typedef struct nyra_waitable_object_t nyra_waitable_number_t;

NYRA_UTILS_API nyra_waitable_number_t *nyra_waitable_number_create(
    int64_t init_value);

NYRA_UTILS_API void nyra_waitable_number_destroy(nyra_waitable_number_t *number);

NYRA_UTILS_API void nyra_waitable_number_increase(nyra_waitable_number_t *number,
                                                int64_t value);

NYRA_UTILS_API void nyra_waitable_number_decrease(nyra_waitable_number_t *number,
                                                int64_t value);

NYRA_UTILS_API void nyra_waitable_number_multiply(nyra_waitable_number_t *number,
                                                int64_t value);

NYRA_UTILS_API void nyra_waitable_number_divide(nyra_waitable_number_t *number,
                                              int64_t value);

NYRA_UTILS_API void nyra_waitable_number_set(nyra_waitable_number_t *number,
                                           int64_t value);

NYRA_UTILS_API int64_t nyra_waitable_number_get(nyra_waitable_number_t *number);

NYRA_UTILS_API int nyra_waitable_number_wait_until(nyra_waitable_number_t *number,
                                                 int64_t value, int timeout);

NYRA_UTILS_API int nyra_waitable_number_wait_while(nyra_waitable_number_t *number,
                                                 int64_t value, int timeout);
