//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
// This file is modified from https://github.com/gpakosz/uuid4/
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>
#include <stdint.h>

#include "nyra_utils/lib/string.h"

typedef uint64_t nyra_uuid4_state_t;

typedef union nyra_uuid4_t {
  uint8_t bytes[16];
  uint32_t dwords[4];
  uint64_t qwords[2];
} nyra_uuid4_t;

NYRA_UTILS_PRIVATE_API uint32_t nyra_uuid4_mix(uint32_t a, uint32_t b);

NYRA_UTILS_PRIVATE_API uint32_t nyra_uuid4_hash(uint32_t value);

/**
 * Seeds the state of the PRNG used to generate version 4 UUIDs.
 *
 * @param a pointer to a variable holding the state.
 *
 * @return `true` on success, otherwise `false`.
 */
NYRA_UTILS_API void nyra_uuid4_seed(nyra_uuid4_state_t *seed);

NYRA_UTILS_API void nyra_uuid4_init_to_zeros(nyra_uuid4_t *self);

/**
 * Generates a version 4 UUID, see https://tools.ietf.org/html/rfc4122.
 *
 * @param state the state of the PRNG used to generate version 4 UUIDs.
 * @param out the recipient for the UUID.
 */
NYRA_UTILS_PRIVATE_API void nyra_uuid4_gen_from_seed(nyra_uuid4_t *self,
                                                   nyra_uuid4_state_t *seed);

NYRA_UTILS_API void nyra_uuid4_gen(nyra_uuid4_t *out);

NYRA_UTILS_API void nyra_uuid4_gen_string(nyra_string_t *out);

NYRA_UTILS_API bool nyra_uuid4_is_equal(const nyra_uuid4_t *a,
                                      const nyra_uuid4_t *b);

NYRA_UTILS_API void nyra_uuid4_copy(nyra_uuid4_t *self, nyra_uuid4_t *src);

NYRA_UTILS_API bool nyra_uuid4_is_empty(nyra_uuid4_t *self);

NYRA_UTILS_API bool nyra_uuid4_from_string(nyra_uuid4_t *self, nyra_string_t *in);

/**
 * Converts a UUID to a `NUL` terminated string.
 * The string format is like 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx', y is either
 * 8, 9, a or b
 *
 * @param out destination ten string
 *
 * @return `true` on success, otherwise `false`.
 */
NYRA_UTILS_API bool nyra_uuid4_to_string(const nyra_uuid4_t *self,
                                       nyra_string_t *out);
