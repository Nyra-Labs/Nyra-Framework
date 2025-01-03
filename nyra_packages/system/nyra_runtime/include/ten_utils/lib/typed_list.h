//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/lib/typed_list_node.h"
#include "nyra_utils/nyra_config.h"

#define NYRA_TYPED_LIST_SIGNATURE 0xF77BB44C7D13991FU

#define nyra_typed_list_foreach(T, list, iter) \
  nyra_typed_list_foreach_(T, list, iter)
#define nyra_typed_list_foreach_(T, list, iter)                                 \
  for (nyra_typed_##T##_list_iterator_t iter =                                  \
           {                                                                   \
               NULL,                                                           \
               nyra_typed_##T##_list_front(list),                               \
               nyra_typed_##T##_list_front(list)                                \
                   ? nyra_typed_##T##_list_front(list)->next                    \
                   : NULL,                                                     \
               0,                                                              \
           };                                                                  \
       (iter).node;                                                            \
       ++((iter).index), (iter).prev = (iter).node, (iter).node = (iter).next, \
                                       (iter).next = (iter).node               \
                                                         ? ((iter).node)->next \
                                                         : NULL)

#define DECLARE_LIST(T) DECLARE_LIST_(T)
#define DECLARE_LIST_(T) \
  typedef struct nyra_typed_##T##_list_t nyra_typed_##T##_list_t

// Because T is surrounded by ## in NYRA_DEFINE_TYPED_LIST_(T), and that would
// prevent T from expanding itself, so the following NYRA_DEFINE_TYPED_LIST() is
// to ensure T is expanded first before entering into NYRA_DEFINE_TYPED_LIST_(T)
#define NYRA_DEFINE_TYPED_LIST(T) NYRA_DEFINE_TYPED_LIST_(T)
#define NYRA_DEFINE_TYPED_LIST_(T)                                             \
  typedef struct nyra_typed_##T##_list_t {                                     \
    nyra_signature_t signature;                                                \
    size_t size;                                                              \
    nyra_typed_##T##_list_node_t *front, *back;                                \
  } nyra_typed_##T##_list_t;                                                   \
                                                                              \
  typedef struct nyra_typed_##T##_list_iterator_t {                            \
    nyra_typed_##T##_list_node_t *prev;                                        \
    nyra_typed_##T##_list_node_t *node;                                        \
    nyra_typed_##T##_list_node_t *next;                                        \
    size_t index;                                                             \
  } nyra_typed_##T##_list_iterator_t;                                          \
                                                                              \
  inline bool nyra_typed_##T##_list_check_integrity(                           \
      nyra_typed_##T##_list_t *self) {                                         \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
                                                                              \
    if (nyra_signature_get(&self->signature) != NYRA_TYPED_LIST_SIGNATURE) {    \
      NYRA_ASSERT(0, "Should not happen.");                                    \
      return false;                                                           \
    }                                                                         \
                                                                              \
    if (!self->size) {                                                        \
      if (self->front != NULL || self->back != NULL) {                        \
        NYRA_ASSERT(0, "Should not happen.");                                  \
        return false;                                                         \
      }                                                                       \
    } else {                                                                  \
      if (self->front == NULL || self->back == NULL) {                        \
        NYRA_ASSERT(0, "Should not happen.");                                  \
        return false;                                                         \
      }                                                                       \
                                                                              \
      if (self->size == 1) {                                                  \
        if (self->front != self->back) {                                      \
          NYRA_ASSERT(0, "Should not happen.");                                \
          return false;                                                       \
        }                                                                     \
        if ((self->front->prev != NULL) || (self->front->next != NULL)) {     \
          NYRA_ASSERT(0, "Should not happen.");                                \
          return false;                                                       \
        }                                                                     \
      }                                                                       \
                                                                              \
      if (self->front->prev != NULL) {                                        \
        NYRA_ASSERT(0, "Should not happen.");                                  \
        return false;                                                         \
      }                                                                       \
      if (self->back->next != NULL) {                                         \
        NYRA_ASSERT(0, "Should not happen.");                                  \
        return false;                                                         \
      }                                                                       \
    }                                                                         \
    return true;                                                              \
  }                                                                           \
                                                                              \
  inline nyra_typed_##T##_list_node_t *nyra_typed_##T##_list_front(             \
      nyra_typed_##T##_list_t *self) {                                         \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(self),                    \
               "Invalid argument.");                                          \
                                                                              \
    return self->front;                                                       \
  }                                                                           \
                                                                              \
  inline nyra_typed_##T##_list_node_t *nyra_typed_##T##_list_back(              \
      nyra_typed_##T##_list_t *self) {                                         \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(self),                    \
               "Invalid argument.");                                          \
                                                                              \
    return self->back;                                                        \
  }                                                                           \
                                                                              \
  inline void nyra_typed_##T##_list_init(nyra_typed_##T##_list_t *self) {       \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
                                                                              \
    nyra_signature_set(&self->signature, NYRA_TYPED_LIST_SIGNATURE);            \
    self->size = 0;                                                           \
    self->front = NULL;                                                       \
    self->back = NULL;                                                        \
  }                                                                           \
                                                                              \
  inline void nyra_typed_##T##_list_clear(nyra_typed_##T##_list_t *self) {      \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(self),                    \
               "Invalid argument.");                                          \
                                                                              \
    nyra_typed_list_foreach(T, self, iter) {                                   \
      nyra_typed_##T##_list_node_destroy(iter.node);                           \
    }                                                                         \
    self->size = 0;                                                           \
    self->front = NULL;                                                       \
    self->back = NULL;                                                        \
  }                                                                           \
                                                                              \
  inline void nyra_typed_##T##_list_deinit(nyra_typed_##T##_list_t *self) {     \
    nyra_typed_##T##_list_clear(self);                                         \
  }                                                                           \
                                                                              \
  inline nyra_typed_##T##_list_t *nyra_typed_##T##_list_create(void) {          \
    nyra_typed_##T##_list_t *self =                                            \
        (nyra_typed_##T##_list_t *)nyra_malloc(sizeof(nyra_typed_##T##_list_t)); \
    NYRA_ASSERT(self, "Failed to allocate memory.");                           \
                                                                              \
    nyra_typed_##T##_list_init(self);                                          \
    return self;                                                              \
  }                                                                           \
                                                                              \
  inline void nyra_typed_##T##_list_destroy(nyra_typed_##T##_list_t *self) {    \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(self),                    \
               "Invalid argument.");                                          \
                                                                              \
    nyra_typed_##T##_list_deinit(self);                                        \
    nyra_free(self);                                                           \
  }                                                                           \
                                                                              \
  inline size_t nyra_typed_##T##_list_size(nyra_typed_##T##_list_t *self) {     \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(self),                    \
               "Invalid argument.");                                          \
                                                                              \
    return self->size;                                                        \
  }                                                                           \
                                                                              \
  inline bool nyra_typed_##T##_list_is_empty(nyra_typed_##T##_list_t *self) {   \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(self),                    \
               "Invalid argument.");                                          \
                                                                              \
    return !nyra_typed_##T##_list_size(self);                                  \
  }                                                                           \
                                                                              \
  inline void nyra_typed_##T##_list_swap(nyra_typed_##T##_list_t *self,         \
                                        nyra_typed_##T##_list_t *target) {     \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
    NYRA_ASSERT(target, "Invalid argument.");                                  \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(self),                    \
               "Invalid argument.");                                          \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(target),                  \
               "Invalid argument.");                                          \
                                                                              \
    nyra_typed_##T##_list_node_t *self_front = self->front;                    \
    nyra_typed_##T##_list_node_t *self_back = self->back;                      \
    size_t self_size = self->size;                                            \
                                                                              \
    self->front = target->front;                                              \
    self->back = target->back;                                                \
    self->size = target->size;                                                \
                                                                              \
    target->front = self_front;                                               \
    target->back = self_back;                                                 \
    target->size = self_size;                                                 \
  }                                                                           \
                                                                              \
  inline void nyra_typed_##T##_list_concat(nyra_typed_##T##_list_t *self,       \
                                          nyra_typed_##T##_list_t *target) {   \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
    NYRA_ASSERT(target, "Invalid argument.");                                  \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(self),                    \
               "Invalid argument.");                                          \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(target),                  \
               "Invalid argument.");                                          \
                                                                              \
    if (nyra_typed_##T##_list_size(target) == 0) {                             \
      return;                                                                 \
    }                                                                         \
                                                                              \
    if (nyra_typed_##T##_list_size(self) == 0) {                               \
      nyra_typed_##T##_list_swap(self, target);                                \
      return;                                                                 \
    }                                                                         \
                                                                              \
    self->back->next = target->front;                                         \
    target->front->prev = self->back;                                         \
    self->back = target->back;                                                \
    self->size += target->size;                                               \
                                                                              \
    target->front = NULL;                                                     \
    target->back = NULL;                                                      \
    target->size = 0;                                                         \
  }                                                                           \
                                                                              \
  inline void nyra_typed_##T##_list_push_front(                                \
      nyra_typed_##T##_list_t *self, nyra_typed_##T##_list_node_t *node) {      \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
    NYRA_ASSERT(node, "Invalid argument.");                                    \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(self),                    \
               "Invalid argument.");                                          \
                                                                              \
    if (nyra_typed_##T##_list_is_empty(self)) {                                \
      self->back = self->front = node;                                        \
      node->prev = node->next = NULL;                                         \
    } else {                                                                  \
      node->next = self->front;                                               \
      node->prev = NULL;                                                      \
                                                                              \
      self->front->prev = node;                                               \
      self->front = node;                                                     \
    }                                                                         \
    ++self->size;                                                             \
  }                                                                           \
                                                                              \
  inline void nyra_typed_##T##_list_push_list_node_back(                       \
      nyra_typed_##T##_list_t *self, nyra_typed_##T##_list_node_t *node) {      \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
    NYRA_ASSERT(node, "Invalid argument.");                                    \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(self),                    \
               "Invalid argument.");                                          \
                                                                              \
    if (nyra_typed_##T##_list_is_empty(self)) {                                \
      self->front = self->back = node;                                        \
      node->next = node->prev = NULL;                                         \
    } else {                                                                  \
      node->next = NULL;                                                      \
      node->prev = self->back;                                                \
                                                                              \
      self->back->next = node;                                                \
      self->back = node;                                                      \
    }                                                                         \
    ++self->size;                                                             \
  }                                                                           \
                                                                              \
  inline void nyra_typed_##T##_list_push_back(                                 \
      nyra_typed_##T##_list_t *self, T item,                                   \
      void (*construct)(T *, void *), /* NOLINT */                            \
      void (*move)(T *, T *),         /* NOLINT */                            \
      void (*copy)(T *, T *),         /* NOLINT */                            \
      void (*destruct)(T *)) {                                                \
    nyra_typed_##T##_list_node_t *item_node =                                  \
        nyra_typed_list_node_create(T)(item, construct, move, copy, destruct); \
    nyra_typed_##T##_list_push_list_node_back(self, item_node);                \
  }                                                                           \
                                                                              \
  inline void nyra_typed_##T##_list_push_back_in_place(                        \
      nyra_typed_##T##_list_t *self, void *data,                               \
      void (*construct)(T *, void *), /* NOLINT */                            \
      void (*move)(T *, T *),         /* NOLINT */                            \
      void (*copy)(T *, T *),         /* NOLINT */                            \
      void (*destruct)(T *)) {                                                \
    nyra_typed_##T##_list_node_t *item_node =                                  \
        nyra_typed_list_node_create_in_place(T)(data, construct, move, copy,   \
                                               destruct);                     \
    nyra_typed_##T##_list_push_list_node_back(self, item_node);                \
  }                                                                           \
                                                                              \
  inline nyra_typed_##T##_list_node_t *nyra_typed_##T##_list_pop_front(         \
      nyra_typed_##T##_list_t *self) {                                         \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(self),                    \
               "Invalid argument.");                                          \
                                                                              \
    if (nyra_typed_##T##_list_is_empty(self)) {                                \
      return NULL;                                                            \
    }                                                                         \
    nyra_typed_##T##_list_node_t *node = self->front;                          \
    if (nyra_typed_##T##_list_size(self) == 1) {                               \
      self->back = self->front = NULL;                                        \
      node->prev = node->next = NULL;                                         \
    } else {                                                                  \
      self->front = self->front->next;                                        \
      self->front->prev = NULL;                                               \
                                                                              \
      node->next = NULL;                                                      \
    }                                                                         \
    --self->size;                                                             \
                                                                              \
    return node;                                                              \
  }                                                                           \
                                                                              \
  inline nyra_typed_##T##_list_node_t *nyra_typed_##T##_list_pop_back(          \
      nyra_typed_##T##_list_t *self) {                                         \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(self),                    \
               "Invalid argument.");                                          \
                                                                              \
    if (nyra_typed_##T##_list_is_empty(self)) {                                \
      return NULL;                                                            \
    }                                                                         \
    nyra_typed_##T##_list_node_t *node = self->back;                           \
    if (nyra_typed_##T##_list_size(self) == 1) {                               \
      self->front = self->back = NULL;                                        \
      node->prev = node->next = NULL;                                         \
    } else {                                                                  \
      self->back = self->back->prev;                                          \
      self->back->next = NULL;                                                \
                                                                              \
      node->prev = NULL;                                                      \
    }                                                                         \
    --self->size;                                                             \
                                                                              \
    return node;                                                              \
  }                                                                           \
                                                                              \
  inline void nyra_typed_##T##_list_copy(nyra_typed_##T##_list_t *self,         \
                                        nyra_typed_##T##_list_t *target) {     \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
    NYRA_ASSERT(target, "Invalid argument.");                                  \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(self),                    \
               "Invalid argument.");                                          \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(target),                  \
               "Invalid argument.");                                          \
                                                                              \
    nyra_typed_list_foreach(T, target, iter) {                                 \
      NYRA_ASSERT(iter.node, "Invalid argument.");                             \
                                                                              \
      nyra_typed_list_node_t(T) *new_node =                                    \
          nyra_typed_list_node_clone(T)(iter.node);                            \
      nyra_typed_list_push_list_node_back(T)(self, new_node);                  \
    }                                                                         \
  }                                                                           \
                                                                              \
  inline nyra_typed_##T##_list_iterator_t nyra_typed_##T##_list_begin(          \
      nyra_typed_##T##_list_t *self) {                                         \
    NYRA_ASSERT(self, "Invalid argument.");                                    \
    NYRA_ASSERT(nyra_typed_##T##_list_check_integrity(self),                    \
               "Invalid argument.");                                          \
                                                                              \
    return (nyra_typed_##T##_list_iterator_t){                                 \
        NULL,                                                                 \
        nyra_typed_##T##_list_front(self),                                     \
        nyra_typed_##T##_list_front(self)                                      \
            ? nyra_typed_##T##_list_front(self)->next                          \
            : NULL,                                                           \
        0,                                                                    \
    };                                                                        \
  }                                                                           \
                                                                              \
  inline nyra_typed_list_node_t(T) *                                           \
      nyra_typed_##T##_list_find(nyra_typed_##T##_list_t *self, T *item,        \
                                bool (*compare)(const T *, const T *)) {      \
    NYRA_ASSERT(                                                               \
        self &&nyra_typed_##T##_list_check_integrity(self) && item && compare, \
        "Invalid argument.");                                                 \
    nyra_typed_list_foreach(T, self, iter) {                                   \
      if (compare(nyra_typed_list_node_get_data(T)(iter.node), item)) {        \
        return iter.node;                                                     \
      }                                                                       \
    }                                                                         \
    return NULL;                                                              \
  }                                                                           \
                                                                              \
  inline nyra_typed_##T##_list_iterator_t nyra_typed_##T##_list_iterator_next(  \
      nyra_typed_##T##_list_iterator_t self) {                                 \
    return (nyra_typed_##T##_list_iterator_t){                                 \
        self.node, self.next, self.node ? (self.node)->next : NULL,           \
        self.index + 1};                                                      \
  }                                                                           \
                                                                              \
  inline bool nyra_typed_##T##_list_iterator_is_end(                           \
      nyra_typed_##T##_list_iterator_t self) {                                 \
    return self.node == NULL;                                                 \
  }                                                                           \
  inline nyra_typed_##T##_list_node_t                                          \
      *nyra_typed_##T##_list_iterator_to_list_node(                            \
          nyra_typed_##T##_list_iterator_t self) {                             \
    return self.node;                                                         \
  }

#define NYRA_TYPED_LIST_INIT_VAL           \
  {.signature = NYRA_TYPED_LIST_SIGNATURE, \
   .size = 0,                             \
   .front = NULL,                         \
   .back = NULL}

#define NYRA_DECLARE_TYPED_LIST_INLINE_ASSETS(T) \
  NYRA_DECLARE_TYPED_LIST_INLINE_ASSETS_(T)
#define NYRA_DECLARE_TYPED_LIST_INLINE_ASSETS_(T)                               \
  extern inline bool nyra_typed_##T##_list_check_integrity(                     \
      nyra_typed_##T##_list_t *self);                                           \
                                                                               \
  extern inline nyra_typed_##T##_list_node_t *nyra_typed_##T##_list_front(       \
      nyra_typed_##T##_list_t *self);                                           \
                                                                               \
  extern inline nyra_typed_##T##_list_node_t *nyra_typed_##T##_list_back(        \
      nyra_typed_##T##_list_t *self);                                           \
                                                                               \
  extern inline void nyra_typed_##T##_list_init(nyra_typed_##T##_list_t *self);  \
                                                                               \
  extern inline void nyra_typed_##T##_list_clear(nyra_typed_##T##_list_t *self); \
                                                                               \
  extern inline void nyra_typed_##T##_list_deinit(                              \
      nyra_typed_##T##_list_t *self);                                           \
                                                                               \
  extern inline nyra_typed_##T##_list_t *nyra_typed_##T##_list_create(void);     \
                                                                               \
  extern inline void nyra_typed_##T##_list_destroy(                             \
      nyra_typed_##T##_list_t *self);                                           \
                                                                               \
  extern inline size_t nyra_typed_##T##_list_size(                              \
      nyra_typed_##T##_list_t *self);                                           \
                                                                               \
  extern inline bool nyra_typed_##T##_list_is_empty(                            \
      nyra_typed_##T##_list_t *self);                                           \
                                                                               \
  extern inline void nyra_typed_##T##_list_swap(                                \
      nyra_typed_##T##_list_t *self, nyra_typed_##T##_list_t *target);           \
                                                                               \
  extern inline void nyra_typed_##T##_list_concat(                              \
      nyra_typed_##T##_list_t *self, nyra_typed_##T##_list_t *target);           \
                                                                               \
  extern inline void nyra_typed_##T##_list_push_front(                          \
      nyra_typed_##T##_list_t *self, nyra_typed_##T##_list_node_t *node);        \
                                                                               \
  extern inline void nyra_typed_##T##_list_push_list_node_back(                 \
      nyra_typed_##T##_list_t *self, nyra_typed_##T##_list_node_t *node);        \
                                                                               \
  extern inline void nyra_typed_##T##_list_push_back(                           \
      nyra_typed_##T##_list_t *self, T item,                                    \
      void (*construct)(T *, void *), /* NOLINT */                             \
      void (*move)(T *, T *),         /* NOLINT */                             \
      void (*copy)(T *, T *),         /* NOLINT */                             \
      void (*destruct)(T *));         /* NOLINT */                             \
                                                                               \
  extern inline void nyra_typed_##T##_list_push_back_in_place(                  \
      nyra_typed_##T##_list_t *self, void *data,                                \
      void (*construct)(T *, void *), /* NOLINT */                             \
      void (*move)(T *, T *),         /* NOLINT */                             \
      void (*copy)(T *, T *),         /* NOLINT */                             \
      void (*destruct)(T *));         /* NOLINT */                             \
                                                                               \
  extern inline nyra_typed_##T##_list_node_t *nyra_typed_##T##_list_pop_front(   \
      nyra_typed_##T##_list_t *self);                                           \
                                                                               \
  extern inline nyra_typed_##T##_list_node_t *nyra_typed_##T##_list_pop_back(    \
      nyra_typed_##T##_list_t *self);                                           \
                                                                               \
  extern inline void nyra_typed_##T##_list_copy(                                \
      nyra_typed_##T##_list_t *self, nyra_typed_##T##_list_t *target);           \
                                                                               \
  extern inline nyra_typed_list_node_t(T) *                                     \
      nyra_typed_##T##_list_find(nyra_typed_##T##_list_t *self, T *item,         \
                                bool (*compare)(const T *, const T *));        \
                                                                               \
  extern inline nyra_typed_##T##_list_iterator_t nyra_typed_##T##_list_begin(    \
      nyra_typed_##T##_list_t *self);                                           \
                                                                               \
  extern inline nyra_typed_##T##_list_iterator_t                                \
      nyra_typed_##T##_list_iterator_next(                                      \
          nyra_typed_##T##_list_iterator_t self);                               \
                                                                               \
  extern inline bool nyra_typed_##T##_list_iterator_is_end(                     \
      nyra_typed_##T##_list_iterator_t self);                                   \
                                                                               \
  extern inline nyra_typed_##T##_list_node_t                                    \
      *nyra_typed_##T##_list_iterator_to_list_node(                             \
          nyra_typed_##T##_list_iterator_t self);

#define nyra_typed_list_t(T) nyra_typed_list_t_(T)
#define nyra_typed_list_t_(T) nyra_typed_##T##_list_t

#define nyra_typed_list_size(T) nyra_typed_list_size_(T)
#define nyra_typed_list_size_(T) nyra_typed_##T##_list_size

#define nyra_typed_list_init(T) nyra_typed_list_init_(T)
#define nyra_typed_list_init_(T) nyra_typed_##T##_list_init

#define nyra_typed_list_deinit(T) nyra_typed_list_deinit_(T)
#define nyra_typed_list_deinit_(T) nyra_typed_##T##_list_deinit

#define nyra_typed_list_create(T) nyra_typed_list_create_(T)
#define nyra_typed_list_create_(T) nyra_typed_##T##_list_create

#define nyra_typed_list_destroy(T) nyra_typed_list_destroy_(T)
#define nyra_typed_list_destroy_(T) nyra_typed_##T##_list_destroy

#define nyra_typed_list_clear(T) nyra_typed_list_clear_(T)
#define nyra_typed_list_clear_(T) nyra_typed_##T##_list_clear

#define nyra_typed_list_copy(T) nyra_typed_list_copy_(T)
#define nyra_typed_list_copy_(T) nyra_typed_##T##_list_copy

#define nyra_typed_list_find(T) nyra_typed_list_find_(T)
#define nyra_typed_list_find_(T) nyra_typed_##T##_list_find

#define nyra_typed_list_front(T) nyra_typed_list_front_(T)
#define nyra_typed_list_front_(T) nyra_typed_##T##_list_front

#define nyra_typed_list_pop_front(T) nyra_typed_list_pop_front_(T)
#define nyra_typed_list_pop_front_(T) nyra_typed_##T##_list_pop_front

#define nyra_typed_list_back(T) nyra_typed_list_back_(T)
#define nyra_typed_list_back_(T) nyra_typed_##T##_list_back

#define nyra_typed_list_push_list_node_back(T) \
  nyra_typed_list_push_list_node_back_(T)
#define nyra_typed_list_push_list_node_back_(T) \
  nyra_typed_##T##_list_push_list_node_back

#define nyra_typed_list_push_back(T) nyra_typed_list_push_back_(T)
#define nyra_typed_list_push_back_(T) nyra_typed_##T##_list_push_back

#define nyra_typed_list_push_back_in_place(T) \
  nyra_typed_list_push_back_in_place_(T)
#define nyra_typed_list_push_back_in_place_(T) \
  nyra_typed_##T##_list_push_back_in_place

#define nyra_typed_list_swap(T) nyra_typed_list_swap_(T)
#define nyra_typed_list_swap_(T) nyra_typed_##T##_list_swap

#define nyra_typed_list_is_empty(T) nyra_typed_list_is_empty_(T)
#define nyra_typed_list_is_empty_(T) nyra_typed_##T##_list_is_empty

#define nyra_typed_list_iterator_t(T) nyra_typed_list_iterator_t_(T)
#define nyra_typed_list_iterator_t_(T) nyra_typed_##T##_list_iterator_t

#define nyra_typed_list_begin(T) nyra_typed_list_begin_(T)
#define nyra_typed_list_begin_(T) nyra_typed_##T##_list_begin

#define nyra_typed_list_iterator_next(T) nyra_typed_list_iterator_next_(T)
#define nyra_typed_list_iterator_next_(T) nyra_typed_##T##_list_iterator_next
