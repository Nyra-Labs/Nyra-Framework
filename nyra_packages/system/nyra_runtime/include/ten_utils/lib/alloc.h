//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stddef.h>

#include "nyra_utils/macro/memory.h"  // IWYU pragma: export

/**
 * @brief Allocate a buffer
 * @param size: Size of buffer
 * @return: Address of buffer if success, NULL otherwise
 */
NYRA_UTILS_API void *nyra_malloc(size_t size);

/**
 * @brief Allocate a buffer
 * @param size: Size of buffer
 * @return: Address of buffer if success, NULL otherwise
 */
NYRA_UTILS_API void *nyra_calloc(size_t cnt, size_t size);

/**
 * @brief Re-allocate a buffer with new size
 * @param p: Address of buffer
 * @param size: New size of buffer
 * @return: Address of buffer if success, NULL otherwise
 */
NYRA_UTILS_API void *nyra_realloc(void *p, size_t size);

/**
 * @brief Deallocate a buffer
 * @param p: Address of buffer
 * @note It is safe to free a NULL pointer
 */
NYRA_UTILS_API void nyra_free(void *p);

/**
 * @brief Duplicate a string
 * @param str: String that needs duplicate
 * @return: Address of new string
 * @note: Please free memory using |nyra_free|
 */
NYRA_UTILS_API char *nyra_strdup(const char *str);

NYRA_UTILS_API void *nyra_malloc_without_backtrace(size_t size);

NYRA_UTILS_API void nyra_free_without_backtrace(void *p);

NYRA_UTILS_API void *nyra_calloc_without_backtrace(size_t cnt, size_t size);

NYRA_UTILS_API void *nyra_realloc_without_backtrace(void *p, size_t size);

NYRA_UTILS_API char *nyra_strdup_without_backtrace(const char *str);
