//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

typedef struct nyra_waitable_object_t nyra_waitable_object_t;

NYRA_UTILS_API nyra_waitable_object_t *nyra_waitable_object_create(
    void *init_value);

NYRA_UTILS_API void nyra_waitable_object_destroy(nyra_waitable_object_t *obj);

NYRA_UTILS_API void nyra_waitable_object_set(nyra_waitable_object_t *obj,
                                           void *value);

NYRA_UTILS_API void *nyra_waitable_object_get(nyra_waitable_object_t *obj);

NYRA_UTILS_API void nyra_waitable_object_update(nyra_waitable_object_t *obj);

NYRA_UTILS_API int nyra_waitable_object_wait_until(nyra_waitable_object_t *obj,
                                                 int (*compare)(const void *l,
                                                                const void *r),
                                                 int timeout);

NYRA_UTILS_API int nyra_waitable_object_wait_while(nyra_waitable_object_t *obj,
                                                 int (*compare)(const void *l,
                                                                const void *r),
                                                 int timeout);
