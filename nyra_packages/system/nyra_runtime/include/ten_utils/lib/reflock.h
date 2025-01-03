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
#include "nyra_utils/lib/event.h"

typedef enum REFLOCK_FLAG {
  NYRA_REFLOCK_REF = (int64_t)0x00000001,
  NYRA_REFLOCK_DESTROY = (int64_t)0x10000000,
  NYRA_REFLOCK_POISON = (int64_t)0x300dead0,
  NYRA_REFLOCK_DESTROY_MASK = (int64_t)0xf0000000,
  NYRA_REFLOCK_REF_MASK = (int64_t)0x0fffffff,
} REFLOCK_FLAG;

typedef struct nyra_reflock_t {
  nyra_atomic_t state;
  nyra_event_t *event;
} nyra_reflock_t;

/**
 * @brief Initialize a reflock.
 * @param reflock The reflock to initialize.
 */
NYRA_UTILS_API void nyra_reflock_init(nyra_reflock_t *lock);

/**
 * @brief Increase the reference count of a reflock.
 * @param reflock The reflock to increase the reference count.
 */
NYRA_UTILS_API void nyra_reflock_ref(nyra_reflock_t *lock);

/**
 * @brief Decrease the reference count of a reflock.
 * @param reflock The reflock to decrease the reference count.
 */
NYRA_UTILS_API void nyra_reflock_unref(nyra_reflock_t *lock);

/**
 * @brief Decrease reference count and destroy after it's zero.
 * @param reflock The reflock to decrease the reference count.
 * @note This function will wait until the reflock is zero
 */
NYRA_UTILS_API void nyra_reflock_unref_destroy(nyra_reflock_t *lock);
