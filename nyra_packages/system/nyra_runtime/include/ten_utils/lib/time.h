//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdint.h>

/**
 * @brief Get the current time in milliseconds.
 * @return The current time in milliseconds.
 * @note The returned value is not steady and is not guaranteed to be monotonic.
 */
NYRA_UTILS_API int64_t nyra_current_time(void);

/**
 * @brief Get the current time in microseconds.
 * @return The current time in milliseconds.
 * @note The returned value is not steady and is not guaranteed to be monotonic.
 */
NYRA_UTILS_API int64_t nyra_current_time_us(void);

/**
 * @brief Sleep for a specified time in milliseconds.
 * @param msec The time to sleep in milliseconds.
 */
NYRA_UTILS_API void nyra_sleep(int64_t msec);

/**
 * @brief Sleep for a random time in milliseconds.
 * @param msec The maximum time to sleep in milliseconds.
 */
NYRA_UTILS_API void nyra_random_sleep(int64_t max_msec);

/**
 * @brief Sleep for a specified time in microseconds.
 * @param msec The time to sleep in microseconds.
 */
NYRA_UTILS_API void nyra_usleep(int64_t usec);
