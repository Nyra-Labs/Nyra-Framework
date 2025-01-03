//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include "nyra_utils/macro/check.h"

#define NYRA_DO_WITH_MUTEX_LOCK(lock, blocks)                  \
  do {                                                        \
    int rc = nyra_mutex_lock(lock);                            \
    NYRA_ASSERT(!rc, "Unable to lock, error code: %d.", rc);   \
                                                              \
    {blocks}                                                  \
                                                              \
    rc = nyra_mutex_unlock(lock);                              \
    NYRA_ASSERT(!rc, "Unable to unlock, error code: %d.", rc); \
  } while (0)

typedef struct nyra_mutex_t nyra_mutex_t;

/**
 * @brief Create a mutex.
 * @return The mutex handle.
 */
NYRA_UTILS_API nyra_mutex_t *nyra_mutex_create(void);

/**
 * @brief Lock a mutex.
 * @param mutex The mutex handle.
 * @return 0 if success, otherwise failed.
 *
 * @note This function will block until the mutex is unlocked.
 */
NYRA_UTILS_API int nyra_mutex_lock(nyra_mutex_t *mutex);

/**
 * @brief Unlock a mutex.
 * @param mutex The mutex handle.
 * @return 0 if success, otherwise failed.
 */
NYRA_UTILS_API int nyra_mutex_unlock(nyra_mutex_t *mutex);

/**
 * @brief Destroy a mutex.
 * @param mutex The mutex handle.
 */
NYRA_UTILS_API void nyra_mutex_destroy(nyra_mutex_t *mutex);

/**
 * @brief Get system mutex handle.
 * @param mutex The mutex handle.
 * @return The system mutex handle.
 */
NYRA_UTILS_API void *nyra_mutex_get_native_handle(nyra_mutex_t *mutex);
