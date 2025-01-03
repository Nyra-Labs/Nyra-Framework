//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdint.h>

#include "nyra_utils/lib/atomic.h"
#include "nyra_utils/lib/waitable_addr.h"

typedef struct nyra_shared_event_t nyra_shared_event_t;

NYRA_UTILS_API nyra_shared_event_t *nyra_shared_event_create(
    uint32_t *addr_for_sig, nyra_atomic_t *addr_for_lock, int init_state,
    int auto_reset);

NYRA_UTILS_API int nyra_shared_event_wait(nyra_shared_event_t *event, int wait_ms);

NYRA_UTILS_API void nyra_shared_event_set(nyra_shared_event_t *event);

NYRA_UTILS_API void nyra_shared_event_reset(nyra_shared_event_t *event);

NYRA_UTILS_API void nyra_shared_event_destroy(nyra_shared_event_t *event);
