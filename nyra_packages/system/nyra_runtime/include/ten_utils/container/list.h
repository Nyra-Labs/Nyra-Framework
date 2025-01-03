//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>
#include <stddef.h>

#include "nyra_utils/container/list_int32.h"  // IWYU pragma: keep
#include "nyra_utils/container/list_node.h"
#include "nyra_utils/container/list_ptr.h"        // IWYU pragma: keep
#include "nyra_utils/container/list_smart_ptr.h"  // IWYU pragma: keep
#include "nyra_utils/container/list_str.h"        // IWYU pragma: keep
#include "nyra_utils/lib/signature.h"

#define NYRA_LIST_SIGNATURE 0x5D6CC60B9833B104U
#define NYRA_LIST_LOOP_MAX_ALLOWABLE_CNT 100000

#define nyra_list_foreach(list, iter)                                           \
  NYRA_ASSERT(nyra_list_size(list) <= NYRA_LIST_LOOP_MAX_ALLOWABLE_CNT,           \
             "The time complexity is too high.");                              \
  for (nyra_list_iterator_t iter = {NULL, nyra_list_front(list),                 \
                                   nyra_list_front(list)                        \
                                       ? nyra_list_front(list)->next            \
                                       : NULL,                                 \
                                   0};                                         \
       (iter).node;                                                            \
       ++((iter).index), (iter).prev = (iter).node, (iter).node = (iter).next, \
                           (iter).next = (iter).node ? ((iter).node)->next     \
                                                     : NULL)

#define NYRA_LIST_INIT_VAL                                                   \
  (nyra_list_t) {                                                            \
    .signature = NYRA_LIST_SIGNATURE, .size = 0, .front = NULL, .back = NULL \
  }

typedef struct nyra_list_t {
  nyra_signature_t signature;
  size_t size;
  nyra_listnode_t *front;
  nyra_listnode_t *back;
} nyra_list_t;

typedef struct nyra_list_iterator_t {
  nyra_listnode_t *prev;
  nyra_listnode_t *node;
  nyra_listnode_t *next;
  size_t index;
} nyra_list_iterator_t;

NYRA_UTILS_API bool nyra_list_check_integrity(nyra_list_t *self);

/**
 * @brief Create a list object.
 * @return A pointer to the list object.
 */
NYRA_UTILS_API nyra_list_t *nyra_list_create(void);

/**
 * @brief Destroy a list object and release the memory.
 * @param self The list object.
 */
NYRA_UTILS_API void nyra_list_destroy(nyra_list_t *self);

/**
 * @brief Initialize a list.
 * @param self The list to be initialized.
 */
NYRA_UTILS_API void nyra_list_init(nyra_list_t *self);

/**
 * @brief Reset a list to an empty list.
 * @param self The list to be reset.
 */
NYRA_UTILS_API void nyra_list_reset(nyra_list_t *self);

/**
 * @brief Clear a list and release all the nodes.
 * @param self The list to be cleared.
 */
NYRA_UTILS_API void nyra_list_clear(nyra_list_t *self);

/**
 * @brief Check if a list is empty.
 * @param self The list to be checked.
 * @return true if the list is empty, false otherwise.
 */
NYRA_UTILS_API bool nyra_list_is_empty(nyra_list_t *self);

/**
 * @brief Get the size of a list.
 * @param self The list to be checked.
 * @return the size of the list.
 */
NYRA_UTILS_API size_t nyra_list_size(nyra_list_t *self);

/**
 * @brief Swap two lists.
 * @param self The list to be swapped.
 * @param target The target list to be swapped.
 */
NYRA_UTILS_API void nyra_list_swap(nyra_list_t *self, nyra_list_t *target);

/**
 * @brief Concatenate two lists.
 * @param self The list to be concatenated.
 * @param target The target list to be concatenated.
 */
NYRA_UTILS_API void nyra_list_concat(nyra_list_t *self, nyra_list_t *target);

/**
 * @brief Remove a node from a list and keep node memory.
 * @param self The list to be removed from.
 * @param node The node to be removed.
 */
NYRA_UTILS_API void nyra_list_detach_node(nyra_list_t *self, nyra_listnode_t *node);

/**
 * @brief Remove a node from a list and release node memory.
 * @param self The list to be removed from.
 * @param node The node to be removed.
 */
NYRA_UTILS_API void nyra_list_remove_node(nyra_list_t *self, nyra_listnode_t *node);

/**
 * @brief Get the front node of a list.
 * @param self The list to be checked.
 * @return the front node of the list. NULL if the list is empty.
 */
NYRA_UTILS_API nyra_listnode_t *nyra_list_front(nyra_list_t *self);

/**
 * @brief Get the back node of a list.
 * @param self The list to be checked.
 * @return the back node of the list. NULL if the list is empty.
 */
NYRA_UTILS_API nyra_listnode_t *nyra_list_back(nyra_list_t *self);

/**
 * @brief Push a node to the front of a list.
 * @param self The list to be pushed to.
 * @param node The node to be pushed.
 */
NYRA_UTILS_API void nyra_list_push_front(nyra_list_t *self, nyra_listnode_t *node);

/**
 * @brief Push a node to the back of a list.
 * @param self The list to be pushed to.
 * @param node The node to be pushed.
 */
NYRA_UTILS_API void nyra_list_push_back(nyra_list_t *self, nyra_listnode_t *node);

/**
 * @brief Pop the front node of a list.
 * @param self The list to be popped from.
 * @return the front node of the list. NULL if the list is empty.
 */
NYRA_UTILS_API nyra_listnode_t *nyra_list_pop_front(nyra_list_t *self);

NYRA_UTILS_API void nyra_list_remove_front(nyra_list_t *self);

/**
 * @brief Pop the back node of a list.
 * @param self The list to be popped from.
 * @return the back node of the list. NULL if the list is empty.
 */
NYRA_UTILS_API nyra_listnode_t *nyra_list_pop_back(nyra_list_t *self);

/**
 * @return
 *  * 1 if left > right
 *  * 0 if left == right
 *  * -1 if left < right
 */
typedef int (*nyra_list_node_compare_func_t)(nyra_listnode_t *left,
                                            nyra_listnode_t *right);

/**
 * @brief Insert a node into a list in order. If the compare function cmp(x, y)
 * returns true, then the node x will stand before the node y in the list.
 *
 * @param self The list to be inserted to.
 * @param node The node to be inserted.
 * @param cmp The compare function.
 * @param skip_if_same If skip_if_same is true, this node won't be pushed into
 * the list if one item in the list equals to it (i.e., cmp(x, node) == 0), and
 * this function will return false.
 *
 * @return Whether this node has been pushed into the list. You have to care
 * about the memory of this node if return false.
 */
NYRA_UTILS_API bool nyra_list_push_back_in_order(nyra_list_t *self,
                                               nyra_listnode_t *node,
                                               nyra_list_node_compare_func_t cmp,
                                               bool skip_if_same);

NYRA_UTILS_API nyra_list_iterator_t nyra_list_begin(nyra_list_t *self);

NYRA_UTILS_API nyra_list_iterator_t nyra_list_end(nyra_list_t *self);

NYRA_UTILS_API nyra_list_iterator_t
nyra_list_iterator_next(nyra_list_iterator_t self);

NYRA_UTILS_API nyra_list_iterator_t
nyra_list_iterator_prev(nyra_list_iterator_t self);

NYRA_UTILS_API bool nyra_list_iterator_is_end(nyra_list_iterator_t self);

NYRA_UTILS_API nyra_listnode_t *nyra_list_iterator_to_listnode(
    nyra_list_iterator_t self);

NYRA_UTILS_API void nyra_list_reverse_new(nyra_list_t *src, nyra_list_t *dest);

NYRA_UTILS_API void nyra_list_reverse(nyra_list_t *src);
