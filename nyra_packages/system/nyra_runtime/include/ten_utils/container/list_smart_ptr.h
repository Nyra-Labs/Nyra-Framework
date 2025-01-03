//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <stdbool.h>

#include "nyra_utils/container/list_node.h"

/**
 * @return The smart_ptr stored in the list.
 */
NYRA_UTILS_API nyra_smart_ptr_t *nyra_list_push_smart_ptr_back(
    nyra_list_t *self, nyra_smart_ptr_t *ptr);

/**
 * @param ptr The raw pointer.
 */
NYRA_UTILS_API nyra_listnode_t *nyra_list_find_shared_ptr(nyra_list_t *self,
                                                       const void *ptr);

#define nyra_list_find_shared_ptr_custom(self, ptr, equal_to) \
  nyra_list_find_shared_ptr_custom_(                          \
      self, ptr, (bool (*)(const void *, const void *))(equal_to))

NYRA_UTILS_API nyra_listnode_t *nyra_list_find_shared_ptr_custom_(
    nyra_list_t *self, const void *ptr,
    bool (*equal_to)(const void *, const void *));

#define nyra_list_find_shared_ptr_custom_2(self, ptr_1, ptr_2, equal_to) \
  nyra_list_find_shared_ptr_custom_2_(                                   \
      self, ptr_1, ptr_2,                                               \
      (bool (*)(const void *, const void *, const void *))(equal_to))

NYRA_UTILS_API nyra_listnode_t *nyra_list_find_shared_ptr_custom_2_(
    nyra_list_t *self, const void *ptr_1, const void *ptr_2,
    bool (*equal_to)(const void *, const void *, const void *));

#define nyra_list_find_shared_ptr_custom_3(self, ptr_1, ptr_2, ptr_3, equal_to) \
  nyra_list_find_shared_ptr_custom_3_(                                          \
      self, ptr_1, ptr_2, ptr_3,                                               \
      (bool (*)(const void *, const void *, const void *, const void *))(      \
          equal_to))

NYRA_UTILS_API nyra_listnode_t *nyra_list_find_shared_ptr_custom_3_(
    nyra_list_t *self, const void *ptr_1, const void *ptr_2, const void *ptr_3,
    bool (*equal_to)(const void *, const void *, const void *, const void *));

#define nyra_list_find_shared_ptr_custom_4(self, ptr_1, ptr_2, ptr_3, ptr_4, \
                                          equal_to)                         \
  nyra_list_find_shared_ptr_custom_4_(                                       \
      self, ptr_1, ptr_2, ptr_3, ptr_4,                                     \
      (bool (*)(const void *, const void *, const void *, const void *,     \
                const void *))(equal_to))

NYRA_UTILS_API nyra_listnode_t *nyra_list_find_shared_ptr_custom_4_(
    nyra_list_t *self, const void *ptr_1, const void *ptr_2, const void *ptr_3,
    const void *ptr_4,
    bool (*equal_to)(const void *, const void *, const void *, const void *,
                     const void *));
