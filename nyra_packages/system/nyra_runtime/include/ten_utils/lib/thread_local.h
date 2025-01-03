//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#if defined(_WIN32)
  #include <Windows.h>
typedef DWORD nyra_thread_key_t;
#else
  #include <pthread.h>
typedef pthread_key_t nyra_thread_key_t;
#endif

#define kInvalidTlsKey ((nyra_thread_key_t) - 1)

/**
 * @brief Create a thread local storage key.
 * @return The key.
 */
NYRA_UTILS_API nyra_thread_key_t nyra_thread_key_create(void);

/**
 * @brief Delete a thread local storage key.
 * @param key The key.
 */
NYRA_UTILS_API void nyra_thread_key_destroy(nyra_thread_key_t key);

/**
 * @brief Set the value of a thread local storage key.
 * @param key The key.
 * @param value The value.
 */
NYRA_UTILS_API int nyra_thread_set_key(nyra_thread_key_t key, void *value);

/**
 * @brief Get the value of a thread local storage key.
 * @param key The key.
 * @return The value.
 */
NYRA_UTILS_API void *nyra_thread_get_key(nyra_thread_key_t key);
