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
#include "nyra_utils/lib/task.h"
#include "nyra_utils/lib/thread.h"

/**
 * This is actually a "busy loop" with "pause" instruction.
 * It's not possible to implement a "real" spin lock in userspace because
 * you have no way to disable thread schedule and interrupts.
 */

typedef struct nyra_spinlock_t {
  nyra_atomic_t lock;
} nyra_spinlock_t;

#define NYRA_SPINLOCK_INIT {0}

/**
 * @brief Initialize a spinlock.
 */
NYRA_UTILS_API void nyra_spinlock_init(nyra_spinlock_t *spin);

/**
 * @brief Initialize a spinlock from address
 * @note If |addr| exists in a shared memory, this lock can be used as IPC lock
 */
NYRA_UTILS_API nyra_spinlock_t *nyra_spinlock_from_addr(nyra_atomic_t *addr);

/**
 * @brief Acquire a spinlock.
 * @note This function will block if the lock is held by others. Recursively
 *       acquire the same lock will result in dead lock
 */
NYRA_UTILS_API void nyra_spinlock_lock(nyra_spinlock_t *spin);

/**
 * @brief Try to acquire a spinlock.
 * @return 0 if the lock is acquired, -1 otherwise.
 */
NYRA_UTILS_API int nyra_spinlock_trylock(nyra_spinlock_t *spin);

/**
 * @brief Release a spinlock.
 */
NYRA_UTILS_API void nyra_spinlock_unlock(nyra_spinlock_t *spin);

typedef struct nyra_recursive_spinlock_t {
  nyra_spinlock_t lock;
  volatile nyra_pid_t pid;
  volatile nyra_tid_t tid;
  volatile int64_t count;
} nyra_recursive_spinlock_t;

#define NYRA_RECURSIVE_SPINLOCK_INIT {NYRA_SPINLOCK_INIT, -1, -1, 0}

/**
 * @brief Initialize a recursive spinlock
 */
NYRA_UTILS_API void nyra_recursive_spinlock_init(nyra_recursive_spinlock_t *spin);

/**
 * @brief Initialize a recursive spinlock from address
 * @note If |addr| exists in a shared memory, this lock can be used as IPC lock
 */
NYRA_UTILS_API nyra_recursive_spinlock_t *nyra_recursive_spinlock_from_addr(
    uint8_t addr[sizeof(nyra_recursive_spinlock_t)]);

/**
 * @brief Acquire a recursive spinlock.
 * @note This function will block if the lock is held by another thread.
 */
NYRA_UTILS_API void nyra_recursive_spinlock_lock(nyra_recursive_spinlock_t *spin);

/**
 * @brief Try to acquire a recursive spinlock.
 * @return 0 if the lock is acquired, -1 otherwise.
 */
NYRA_UTILS_API int nyra_recursive_spinlock_trylock(
    nyra_recursive_spinlock_t *spin);

/**
 * @brief Release a recursive spinlock.
 */
NYRA_UTILS_API void nyra_recursive_spinlock_unlock(
    nyra_recursive_spinlock_t *spin);
