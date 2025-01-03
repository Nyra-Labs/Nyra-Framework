//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>

#include "nyra_utils/lib/atomic.h"
#include "nyra_utils/sanitizer/thread_check.h"

/**
 * @brief The internal architecture of a shared_ptr/weak_ptr is as follows.
 *
 * shared_ptr \
 * shared_ptr -> ctrl_blk -> data
 *   weak_ptr /
 *
 * A shared_ptr would contribute 1 'shared_cnt' (and additional 1 'weak_cnt' for
 * the 1st shared_ptr), and a weak_ptr would contribute 1 'weak_cnt' only.
 */

typedef enum NYRA_SMART_PTR_TYPE {
  NYRA_SMART_PTR_SHARED,
  NYRA_SMART_PTR_WEAK,
} NYRA_SMART_PTR_TYPE;

typedef struct nyra_smart_ptr_ctrl_blk_t {
  nyra_atomic_t shared_cnt;
  nyra_atomic_t weak_cnt;

  void *data;  // Points to the shared data.
  void (*destroy)(void *data);
} nyra_smart_ptr_ctrl_blk_t;

typedef struct nyra_smart_ptr_t {
  nyra_signature_t signature;
  nyra_sanitizer_thread_check_t thread_check;

  NYRA_SMART_PTR_TYPE type;

  // Control the life of the memory space pointed by this nyra_smart_ptr_t
  // object.
  nyra_smart_ptr_ctrl_blk_t *ctrl_blk;
} nyra_smart_ptr_t;

typedef nyra_smart_ptr_t nyra_shared_ptr_t;
typedef nyra_smart_ptr_t nyra_weak_ptr_t;

typedef bool (*nyra_smart_ptr_type_checker)(void *data);

// @{
// Smart pointer

NYRA_UTILS_PRIVATE_API nyra_smart_ptr_t *nyra_smart_ptr_clone(
    nyra_smart_ptr_t *other);

/**
 * @brief Destroy a smart_ptr.
 */
NYRA_UTILS_PRIVATE_API void nyra_smart_ptr_destroy(nyra_smart_ptr_t *self);

/**
 * @brief This function must be used with caution. Essentially, this function
 * can only be used within the NYRA runtime and should not be accessed
 * externally. This is because if the parameter is actually a weak_ptr, the
 * function expects the weak_ptr to remain valid after the completion of the
 * function, meaning the object pointed to by the weak_ptr remains valid after
 * the function ends.
 */
NYRA_UTILS_API void *nyra_smart_ptr_get_data(nyra_smart_ptr_t *self);

NYRA_UTILS_API bool nyra_smart_ptr_check_type(
    nyra_smart_ptr_t *self, nyra_smart_ptr_type_checker type_checker);

// @}

// @{
// Shared pointer

#ifdef __cplusplus
  #define nyra_shared_ptr_create(ptr, destroy) \
    nyra_shared_ptr_create_(ptr, reinterpret_cast<void (*)(void *)>(destroy))
#else
  #define nyra_shared_ptr_create(ptr, destroy) \
    nyra_shared_ptr_create_(ptr, (void (*)(void *))(destroy))
#endif

NYRA_UTILS_API nyra_shared_ptr_t *nyra_shared_ptr_create_(void *ptr,
                                                       void (*destroy)(void *));

NYRA_UTILS_API nyra_shared_ptr_t *nyra_shared_ptr_clone(nyra_shared_ptr_t *other);

NYRA_UTILS_API void nyra_shared_ptr_destroy(nyra_shared_ptr_t *self);

/**
 * @brief Get the pointing resource.
 */
NYRA_UTILS_API void *nyra_shared_ptr_get_data(nyra_shared_ptr_t *self);

// @}

// @{
// Weak pointer

/**
 * @brief Create a weak_ptr from a shared_ptr.
 *
 * @note This function expects that @a shared_ptr is valid.
 */
NYRA_UTILS_API nyra_weak_ptr_t *nyra_weak_ptr_create(nyra_shared_ptr_t *shared_ptr);

NYRA_UTILS_API nyra_weak_ptr_t *nyra_weak_ptr_clone(nyra_weak_ptr_t *other);

NYRA_UTILS_API void nyra_weak_ptr_destroy(nyra_weak_ptr_t *self);

/**
 * @brief Convert a weak pointer into a shared pointer if the pointing
 * resource is still available.
 */
NYRA_UTILS_API nyra_shared_ptr_t *nyra_weak_ptr_lock(nyra_weak_ptr_t *self);

// @}
