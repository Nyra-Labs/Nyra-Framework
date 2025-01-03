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
#include "nyra_utils/lib/signature.h"

#define NYRA_REF_SIGNATURE 0x759D8D9D2661E36BU

typedef struct nyra_ref_t nyra_ref_t;

typedef void (*nyra_ref_on_end_of_life_func_t)(nyra_ref_t *ref, void *supervisee);

typedef struct nyra_ref_t {
  nyra_signature_t signature;

  nyra_atomic_t ref_cnt;

  // The object which is managed by this 'nyra_ref_t'. This field should _not_ be
  // modified after 'nyra_ref_t' has been initted, therefore, we don't need to
  // care about its thread safety.
  void *supervisee;

  // This function will be called when the end-of-life of 'supervisee' is
  // reached. This field should _not_ be modified after 'nyra_ref_t' has been
  // initted, therefore, we don't need to care about its thread safety.
  nyra_ref_on_end_of_life_func_t on_end_of_life;
} nyra_ref_t;

/**
 * @param on_end_of_line Required. If the 'nyra_ref_t' object in @a supervisee is
 * a pointer, you _must_ call 'nyra_ref_destroy()' in @a on_end_of_life. And if
 * the 'nyra_ref_t' object is an embedded field in @a supervisee, you _must_ call
 * 'nyra_ref_deinit()' in @a on_end_of_life.
 */
NYRA_UTILS_API nyra_ref_t *nyra_ref_create(
    void *supervisee, nyra_ref_on_end_of_life_func_t on_end_of_life);

/**
 * @brief No matter what the ref_cnt is, force terminate nyra_ref_t.
 *
 * @note Use with caution.
 */
NYRA_UTILS_API void nyra_ref_destroy(nyra_ref_t *self);

/**
 * @param on_end_of_line Required. If the 'nyra_ref_t' object in @a supervisee is
 * a pointer, you _must_ call 'nyra_ref_destroy()' in @a on_end_of_life. And if
 * the 'nyra_ref_t' object is an embedded field in @a supervisee, you _must_ call
 * 'nyra_ref_deinit()' in @a on_end_of_life.
 */
NYRA_UTILS_API void nyra_ref_init(nyra_ref_t *self, void *supervisee,
                                nyra_ref_on_end_of_life_func_t on_end_of_life);

NYRA_UTILS_API void nyra_ref_deinit(nyra_ref_t *self);

NYRA_UTILS_API bool nyra_ref_inc_ref(nyra_ref_t *self);

NYRA_UTILS_API bool nyra_ref_dec_ref(nyra_ref_t *self);

NYRA_UTILS_API int64_t nyra_ref_get_ref(nyra_ref_t *self);
