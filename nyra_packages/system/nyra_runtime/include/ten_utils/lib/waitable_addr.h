//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdint.h>

typedef struct nyra_spinlock_t nyra_spinlock_t;
typedef struct nyra_waitable_t {
  uint32_t sig;
} nyra_waitable_t;

#define NYRA_WAITABLE_INIT {0}

NYRA_UTILS_API void nyra_waitable_init(nyra_waitable_t *wb);

NYRA_UTILS_API nyra_waitable_t *nyra_waitable_from_addr(uint32_t *address);

NYRA_UTILS_API int nyra_waitable_wait(nyra_waitable_t *wb, uint32_t expect,
                                    nyra_spinlock_t *lock, int timeout);

NYRA_UTILS_API void nyra_waitable_notify(nyra_waitable_t *wb);

NYRA_UTILS_API void nyra_waitable_notify_all(nyra_waitable_t *wb);

NYRA_UTILS_API uint32_t nyra_waitable_get(nyra_waitable_t *wb);

NYRA_UTILS_API void nyra_waitable_set(nyra_waitable_t *wb, uint32_t val);
