//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#define PTR_FILL_VALUE(ptr, value)                  \
  ({                                                \
    *(typeof(value) *)ptr = value;                  \
    ptr = nyra_ptr_move_in_byte(ptr, sizeof(value)); \
  })

#define PTR_FILL_STR(ptr, str)                    \
  ({                                              \
    *(typeof(value) *)ptr = value;                \
    strcpy(ptr, str);                             \
    ptr = nyra_ptr_move_in_byte(ptr, strlen(str)); \
  })

// NOLINTNEXTLINE(clang-diagnostic-unused-function)
static inline void *nyra_ptr_move_in_byte(void *ptr, ptrdiff_t offset) {
  assert(ptr);
  return (void *)((uint8_t *)ptr + offset);
}

// NOLINTNEXTLINE(clang-diagnostic-unused-function)
static inline const void *nyra_const_ptr_move_in_byte(const void *ptr,
                                                     ptrdiff_t offset) {
  assert(ptr);
  return (const void *)((const uint8_t *)ptr + offset);
}

// NOLINTNEXTLINE(clang-diagnostic-unused-function)
static inline ptrdiff_t nyra_ptr_diff_in_byte(void *a, void *b) {
  assert(a && b && a >= b);
  return (uint8_t *)a - (uint8_t *)b;
}

// NOLINTNEXTLINE(clang-diagnostic-unused-function)
static inline ptrdiff_t nyra_const_ptr_diff_in_byte(const void *a,
                                                   const void *b) {
  assert(a && b && a >= b);
  return (const uint8_t *)a - (const uint8_t *)b;
}
