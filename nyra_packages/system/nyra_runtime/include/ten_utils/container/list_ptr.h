//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "nyra_utils/container/list_node.h"

#define nyra_list_find_ptr_custom(self, ptr, equal_to)  \
  nyra_list_find_ptr_custom_(self, (const void *)(ptr), \
                            (bool (*)(const void *, const void *))(equal_to));

NYRA_UTILS_API nyra_listnode_t *nyra_list_find_ptr_custom_(
    nyra_list_t *self, const void *ptr,
    bool (*equal_to)(const void *, const void *));

#define nyra_list_find_ptr_cnt_custom(self, ptr, equal_to) \
  nyra_list_find_ptr_cnt_custom_(                          \
      self, (const void *)(ptr),                          \
      (bool (*)(const void *, const void *))(equal_to));

NYRA_UTILS_API size_t
nyra_list_find_ptr_cnt_custom_(nyra_list_t *self, const void *ptr,
                              bool (*equal_to)(const void *, const void *));

#define nyra_list_cnt_ptr_custom(self, predicate) \
  nyra_list_cnt_ptr_custom_(self, (bool (*)(const void *))(predicate));

NYRA_UTILS_API size_t nyra_list_cnt_ptr_custom_(nyra_list_t *self,
                                              bool (*predicate)(const void *));

NYRA_UTILS_API nyra_listnode_t *nyra_list_find_ptr(nyra_list_t *self,
                                                const void *ptr);

NYRA_UTILS_API bool nyra_list_remove_ptr(nyra_list_t *self, void *ptr);

NYRA_UTILS_API void nyra_list_push_ptr_back(
    nyra_list_t *self, void *ptr, nyra_ptr_listnode_destroy_func_t destroy);

NYRAA_UTILS_API void nyra_list_push_ptr_front(
    nyra_list_t *self, void *ptr, nyra_ptr_listnode_destroy_func_t destroy);
