//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include "nyra_utils/macro/check.h"

#define NYRA_TYPED_LIST_NODE_SIGNATURE 0x3CE1EAC77F72D345U

/**
 * @brief Because T is surrounded by ## in NYRA_DEFINE_TYPED_LIST_NODE_(T), and
 * that would prevent T from expanding itself, so the following
 * NYRA_DEFINE_TYPED_LIST_NODE() is to ensure T is expanded first before entering
 * into NYRA_DEFINE_TYPED_LIST_NODE_(T)
 *
 * @param T The type of the value stored in the list node.
 */
#define NYRA_DEFINE_TYPED_LIST_NODE(T) NYRA_DEFINE_TYPED_LIST_NODE_(T)
#define NYRA_DEFINE_TYPED_LIST_NODE_(T)                                         \
  typedef struct nyra_typed_##T##_list_node_t nyra_typed_##T##_list_node_t;      \
  struct nyra_typed_##T##_list_node_t {                                         \
    nyra_signature_t signature;                                                 \
    nyra_typed_##T##_list_node_t *next, *prev;                                  \
    T data;                                                                    \
    void (*construct)(T *, void *); /* NOLINT */                               \
    void (*move)(T *, T *);         /* NOLINT */                               \
    void (*copy)(T *, T *);         /* NOLINT */                               \
    void (*destruct)(T *);          /* NOLINT */                               \
  };                                                                           \
                                                                               \
  inline bool nyra_typed_##T##_list_node_check_integrity(                       \
      nyra_typed_##T##_list_node_t *self) {                                     \
    NYRA_ASSERT(self, "Invalid argument.");                                     \
                                                                               \
    if (nyra_signature_get(&self->signature) !=                                 \
        NYRA_TYPED_LIST_NODE_SIGNATURE) {                                       \
      NYRA_ASSERT(0, "Should not happen.");                                     \
      return false;                                                            \
    }                                                                          \
    return true;                                                               \
  }                                                                            \
                                                                               \
  inline bool nyra_typed_##T##_list_node_init_empty(                            \
      nyra_typed_##T##_list_node_t *self, void (*construct)(T *, void *),       \
      void (*move)(T *, T *),  /* NOLINT */                                    \
      void (*copy)(T *, T *),  /* NOLINT */                                    \
      void (*destruct)(T *)) { /* NOLINT */                                    \
    NYRA_ASSERT(self, "Invalid argument.");                                     \
                                                                               \
    nyra_signature_set(&self->signature, NYRA_TYPED_LIST_NODE_SIGNATURE);        \
    self->next = NULL;                                                         \
    self->prev = NULL;                                                         \
                                                                               \
    self->construct = construct;                                               \
    self->move = move;                                                         \
    self->copy = copy;                                                         \
    self->destruct = destruct;                                                 \
                                                                               \
    return true;                                                               \
  }                                                                            \
                                                                               \
  inline bool nyra_typed_##T##_list_node_init(                                  \
      nyra_typed_##T##_list_node_t *self, T data,                               \
      void (*construct)(T *, void *), /* NOLINT */                             \
      void (*move)(T *, T *),         /* NOLINT */                             \
      void (*copy)(T *, T *),         /* NOLINT */                             \
      void (*destruct)(T *)) {        /* NOLINT */                             \
    nyra_typed_##T##_list_node_init_empty(self, construct, move, copy,          \
                                         destruct);                            \
    self->data = data;                                                         \
    return true;                                                               \
  }                                                                            \
                                                                               \
  inline bool nyra_typed_##T##_list_node_init_in_place(                         \
      nyra_typed_##T##_list_node_t *self, void *data,                           \
      void (*construct)(T *, void *), /* NOLINT */                             \
      void (*move)(T *, T *),         /* NOLINT */                             \
      void (*copy)(T *, T *),         /* NOLINT */                             \
      void (*destruct)(T *)) {        /* NOLINT */                             \
    nyra_typed_##T##_list_node_init_empty(self, construct, move, copy,          \
                                         destruct);                            \
    if (construct) {                                                           \
      construct(&self->data, data);                                            \
    }                                                                          \
    return true;                                                               \
  }                                                                            \
                                                                               \
  inline nyra_typed_##T##_list_node_t *nyra_typed_##T##_list_node_create_empty(  \
      void (*construct)(T *, void *), /* NOLINT */                             \
      void (*move)(T *, T *),         /* NOLINT */                             \
      void (*copy)(T *, T *),         /* NOLINT */                             \
      void (*destruct)(T *)) {        /* NOLINT */                             \
    nyra_typed_##T##_list_node_t *self =                                        \
        (nyra_typed_##T##_list_node_t *)nyra_malloc(                             \
            sizeof(nyra_typed_##T##_list_node_t));                              \
    NYRA_ASSERT(self, "Failed to allocate memory.");                            \
                                                                               \
    nyra_typed_##T##_list_node_init_empty(self, construct, move, copy,          \
                                         destruct);                            \
                                                                               \
    return self;                                                               \
  }                                                                            \
                                                                               \
  inline nyra_typed_##T##_list_node_t *nyra_typed_##T##_list_node_create(        \
      T data, void (*construct)(T *, void *), /* NOLINT */                     \
      void (*move)(T *, T *),                 /* NOLINT */                     \
      void (*copy)(T *, T *),                 /* NOLINT */                     \
      void (*destruct)(T *)) {                /* NOLINT */                     \
    nyra_typed_##T##_list_node_t *self =                                        \
        (nyra_typed_##T##_list_node_t *)nyra_malloc(                             \
            sizeof(nyra_typed_##T##_list_node_t));                              \
    NYRA_ASSERT(self, "Failed to allocate memory.");                            \
                                                                               \
    nyra_typed_##T##_list_node_init(self, data, construct, move, copy,          \
                                   destruct);                                  \
    return self;                                                               \
  }                                                                            \
                                                                               \
  inline nyra_typed_##T##_list_node_t                                           \
      *nyra_typed_##T##_list_node_create_in_place(                              \
          void *data, void (*construct)(T *, void *), /* NOLINT */             \
          void (*move)(T *, T *),                     /* NOLINT */             \
          void (*copy)(T *, T *),                     /* NOLINT */             \
          void (*destruct)(T *)) {                    /* NOLINT */             \
    nyra_typed_##T##_list_node_t *self =                                        \
        (nyra_typed_##T##_list_node_t *)nyra_malloc(                             \
            sizeof(nyra_typed_##T##_list_node_t));                              \
    NYRA_ASSERT(self, "Failed to allocate memory.");                            \
                                                                               \
    nyra_typed_##T##_list_node_init_in_place(self, data, construct, move, copy, \
                                            destruct);                         \
    return self;                                                               \
  }                                                                            \
                                                                               \
  inline nyra_typed_##T##_list_node_t *nyra_typed_##T##_list_node_clone(         \
      nyra_typed_##T##_list_node_t *src) {                                      \
    NYRA_ASSERT(src, "Invalid argument.");                                      \
                                                                               \
    /* NOLINTNEXTLINE(cppcoreguidelines-pro-type-cstyle-cast) */               \
    nyra_typed_##T##_list_node_t *self =                                        \
        (nyra_typed_##T##_list_node_t *)nyra_malloc(                             \
            sizeof(nyra_typed_##T##_list_node_t));                              \
    NYRA_ASSERT(self, "Failed to allocate memory.");                            \
                                                                               \
    nyra_typed_##T##_list_node_init_empty(self, src->construct, src->move,      \
                                         src->copy, src->destruct);            \
    src->copy(&self->data, &src->data);                                        \
    return self;                                                               \
  }                                                                            \
                                                                               \
  inline bool nyra_typed_##T##_list_node_deinit(                                \
      nyra_typed_##T##_list_node_t *self) {                                     \
    NYRA_ASSERT(self, "Invalid argument.");                                     \
    NYRA_ASSERT(nyra_typed_##T##_list_node_check_integrity(self),                \
               "Invalid argument.");                                           \
                                                                               \
    if (self->destruct) {                                                      \
      self->destruct(&(self->data));                                           \
    }                                                                          \
    return true;                                                               \
  }                                                                            \
                                                                               \
  inline bool nyra_typed_##T##_list_node_destroy(                               \
      nyra_typed_##T##_list_node_t *self) {                                     \
    NYRA_ASSERT(self, "Invalid argument.");                                     \
    NYRA_ASSERT(nyra_typed_##T##_list_node_check_integrity(self),                \
               "Invalid argument.");                                           \
                                                                               \
    if (!nyra_typed_##T##_list_node_deinit(self)) {                             \
      return false;                                                            \
    }                                                                          \
    nyra_free(self);                                                            \
    return true;                                                               \
  }                                                                            \
                                                                               \
  /* NOLINTNEXTLINE */                                                         \
  inline T *nyra_typed_##T##_list_node_get_data(                                \
      nyra_typed_##T##_list_node_t *self) {                                     \
    NYRA_ASSERT(self, "Invalid argument.");                                     \
    NYRA_ASSERT(nyra_typed_##T##_list_node_check_integrity(self),                \
               "Invalid argument.");                                           \
                                                                               \
    return &self->data;                                                        \
  }                                                                            \
                                                                               \
  inline bool nyra_typed_##T##_list_node_set_data(                              \
      nyra_typed_##T##_list_node_t *self, T *data, bool move) { /* NOLINT */    \
    NYRA_ASSERT(self, "Invalid argument.");                                     \
    NYRA_ASSERT(nyra_typed_##T##_list_node_check_integrity(self),                \
               "Invalid argument.");                                           \
                                                                               \
    /* Destruct the old data if any */                                         \
    if (self->destruct) {                                                      \
      self->destruct(&self->data);                                             \
    }                                                                          \
    if (move) {                                                                \
      if (self->move) {                                                        \
        self->move(&self->data, data);                                         \
      } else {                                                                 \
        self->data = *data;                                                    \
      }                                                                        \
    } else {                                                                   \
      if (self->copy) {                                                        \
        self->copy(&self->data, data);                                         \
      } else {                                                                 \
        self->data = *data;                                                    \
      }                                                                        \
    }                                                                          \
    return true;                                                               \
  }

#define NYRA_DECLARE_TYPED_LIST_NODE_INLINE_ASSETS(T) \
  NYRA_DECLARE_TYPED_LIST_NODE_INLINE_ASSETS_(T)
#define NYRA_DECLARE_TYPED_LIST_NODE_INLINE_ASSETS_(T)                          \
  extern inline bool nyra_typed_##T##_list_node_check_integrity(                \
      nyra_typed_##T##_list_node_t *self);                                      \
                                                                               \
  extern inline bool nyra_typed_##T##_list_node_init_empty(                     \
      nyra_typed_##T##_list_node_t *self,                                       \
      void (*construct)(T *, void *), /* NOLINT */                             \
      void (*move)(T *, T *),         /* NOLINT */                             \
      void (*copy)(T *, T *),         /* NOLINT */                             \
      void (*destruct)(T *));                                                  \
                                                                               \
  extern inline bool nyra_typed_##T##_list_node_init(                           \
      nyra_typed_##T##_list_node_t *self, T data,                               \
      void (*construct)(T *, void *), /* NOLINT */                             \
      void (*move)(T *, T *),         /* NOLINT */                             \
      void (*copy)(T *, T *),         /* NOLINT */                             \
      void (*destruct)(T *));                                                  \
                                                                               \
  extern inline bool nyra_typed_##T##_list_node_init_in_place(                  \
      nyra_typed_##T##_list_node_t *self, void *data,                           \
      void (*construct)(T *, void *), /* NOLINT */                             \
      void (*move)(T *, T *),         /* NOLINT */                             \
      void (*copy)(T *, T *),         /* NOLINT */                             \
      void (*destruct)(T *));                                                  \
                                                                               \
  extern inline nyra_typed_##T##_list_node_t                                    \
      *nyra_typed_##T##_list_node_create_empty(                                 \
          void (*construct)(T *, void *), /* NOLINT */                         \
          void (*move)(T *, T *),         /* NOLINT */                         \
          void (*copy)(T *, T *),         /* NOLINT */                         \
          void (*destruct)(T *));                                              \
                                                                               \
  extern inline nyra_typed_##T##_list_node_t *nyra_typed_##T##_list_node_create( \
      T data, void (*construct)(T *, void *), /* NOLINT */                     \
      void (*move)(T *, T *),                 /* NOLINT */                     \
      void (*copy)(T *, T *),                 /* NOLINT */                     \
      void (*destruct)(T *));                                                  \
                                                                               \
  extern inline nyra_typed_##T##_list_node_t                                    \
      *nyra_typed_##T##_list_node_create_in_place(                              \
          void *data, void (*construct)(T *, void *), /* NOLINT */             \
          void (*move)(T *, T *),                     /* NOLINT */             \
          void (*copy)(T *, T *),                     /* NOLINT */             \
          void (*destruct)(T *));                                              \
                                                                               \
  extern inline nyra_typed_##T##_list_node_t *nyra_typed_##T##_list_node_clone(  \
      nyra_typed_##T##_list_node_t *src);                                       \
                                                                               \
  extern inline bool nyra_typed_##T##_list_node_deinit(                         \
      nyra_typed_##T##_list_node_t *self);                                      \
                                                                               \
  extern inline bool nyra_typed_##T##_list_node_destroy(                        \
      nyra_typed_##T##_list_node_t *self);                                      \
                                                                               \
  /* NOLINTNEXTLINE */                                                         \
  extern inline T *nyra_typed_##T##_list_node_get_data(                         \
      nyra_typed_##T##_list_node_t *self);                                      \
                                                                               \
  extern inline bool nyra_typed_##T##_list_node_set_data(                       \
      nyra_typed_##T##_list_node_t *self, T *data, bool move);

#define nyra_typed_list_node_t(T) nyra_typed_list_node_t_(T)
#define nyra_typed_list_node_t_(T) nyra_typed_##T##_list_node_t

#define nyra_typed_list_node_init(T) nyra_typed_list_node_init_(T)
#define nyra_typed_list_node_init_(T) nyra_typed_##T##_list_node_init

#define nyra_typed_list_node_init_in_place(T) \
  nyra_typed_list_node_init_in_place_(T)
#define nyra_typed_list_node_init_in_place_(T) \
  nyra_typed_##T##_list_node_init_in_place

#define nyra_typed_list_node_create_empty(T) nyra_typed_list_node_create_empty_(T)
#define nyra_typed_list_node_create_empty_(T) \
  nyra_typed_##T##_list_node_create_empty

#define nyra_typed_list_node_create(T) nyra_typed_list_node_create_(T)
#define nyra_typed_list_node_create_(T) nyra_typed_##T##_list_node_create

#define nyra_typed_list_node_create_in_place(T) \
  nyra_typed_list_node_create_in_place_(T)
#define nyra_typed_list_node_create_in_place_(T) \
  nyra_typed_##T##_list_node_create_in_place

#define nyra_typed_list_node_clone(T) nyra_typed_list_node_clone_(T)
#define nyra_typed_list_node_clone_(T) nyra_typed_##T##_list_node_clone

#define nyra_typed_list_node_deinit(T) nyra_typed_list_node_deinit_(T)
#define nyra_typed_list_node_deinit_(T) nyra_typed_##T##_list_node_deinit

#define nyra_typed_list_node_destroy(T) nyra_typed_list_node_destroy_(T)
#define nyra_typed_list_node_destroy_(T) nyra_typed_##T##_list_node_destroy

#define nyra_typed_list_node_get_data(T) nyra_typed_list_node_get_data_(T)
#define nyra_typed_list_node_get_data_(T) nyra_typed_##T##_list_node_get_data

#define nyra_typed_list_node_set_data(T) nyra_typed_list_node_set_data_(T)
#define nyra_typed_list_node_set_data_(T) nyra_typed_##T##_list_node_set_data
