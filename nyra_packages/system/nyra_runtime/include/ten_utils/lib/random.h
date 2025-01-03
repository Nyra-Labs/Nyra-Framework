//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stddef.h>

/**
 * @brief Generate random buffer with given size.
 * @param buf The buffer to store random data.
 * @param size The size of the buffer.
 * @return 0 on success, -1 on failure.
 *
 * This function generates random data. It may fail.
 */
NYRA_UTILS_API int nyra_random(void *buf, size_t size);

/**
 * @brief Generate random int n that start <= n < end
 * @param start The begin of random.
 * @param end The end of random.
 * @return A random int number
 */
NYRA_UTILS_API int nyra_random_int(int start, int end);

/**
 * @brief Generate random printable string with given size.
 * @param buf The buffer to store random data.
 * @param size The size of the buffer.
 * @return 0 on success, -1 on failure.
 */
NYRA_UTILS_API int nyra_random_string(char *buf, size_t size);

/**
 * @brief Generate random hex string with given size.
 * @param buf The buffer to store random data.
 * @param size The size of the buffer.
 */
NYRA_UTILS_API int nyra_random_hex_string(char *buf, size_t size);

/**
 * @brief Generate random base64 string with given size.
 * @param buf The buffer to store random data.
 * @param size The size of the buffer.
 */
NYRA_UTILS_API int nyra_random_base64_string(char *buf, size_t size);

/**
 * @brief Generate UUID string.
 * @param buf The buffer to store random data.
 * @param size The size of the buffer.
 */
NYRA_UTILS_API int nyra_uuid_new(char *buf, size_t size);
