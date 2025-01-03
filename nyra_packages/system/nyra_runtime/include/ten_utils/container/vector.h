//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#include "nyra_utils/nyra_config.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct nyra_vector_t {
  void *data;
  size_t size;
  size_t capacity;
} nyra_vector_t;

NYRA_UTILS_API void nyra_vector_init(nyra_vector_t *self, size_t capacity);

/**
 * Create a new vector of the given capacity.
 */
NYRA_UTILS_API nyra_vector_t *nyra_vector_create(size_t capacity);

NYRA_UTILS_API void nyra_vector_deinit(nyra_vector_t *self);

/**
 * Free vector related memory.
 */
NYRA_UTILS_API void nyra_vector_destroy(nyra_vector_t *self);

NYRA_UTILS_API void *nyra_vector_grow(nyra_vector_t *self, size_t size);

NYRA_UTILS_API bool nyra_vector_release_remaining_space(nyra_vector_t *self);

NYRA_UTILS_API void *nyra_vector_take_out(nyra_vector_t *self);
