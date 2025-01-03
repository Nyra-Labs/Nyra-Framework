//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

typedef struct nyra_process_mutex_t nyra_process_mutex_t;

/**
 * @brief Create a mutex.
 * @return The mutex handle.
 */
NYRA_UTILS_API nyra_process_mutex_t *nyra_process_mutex_create(const char *name);

/**
 * @brief Lock a mutex.
 * @param mutex The mutex handle.
 * @return 0 if success, otherwise failed.
 *
 * @note This function will block until the mutex is unlocked.
 */
NYRA_UTILS_API int nyra_process_mutex_lock(nyra_process_mutex_t *mutex);

/**
 * @brief Unlock a mutex.
 * @param mutex The mutex handle.
 * @return 0 if success, otherwise failed.
 */
NYRA_UTILS_API int nyra_process_mutex_unlock(nyra_process_mutex_t *mutex);

/**
 * @brief Destroy a mutex.
 * @param mutex The mutex handle.
 */
NYRA_UTILS_API void nyra_process_mutex_destroy(nyra_process_mutex_t *mutex);
