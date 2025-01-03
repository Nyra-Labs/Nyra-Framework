//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>

#include "nyra_utils/container/list_node.h"
#include "nyra_utils/lib/signature.h"

#define NYRA_NORMAL_PTR_LISTNODE_SIGNATURE 0xEBB1285007CA4A12U

typedef void (*nyra_ptr_listnode_destroy_func_t)(void *ptr);

typedef struct nyra_ptr_listnode_t {
  nyra_listnode_t hdr;
  nyra_signature_t signature;
  void *ptr;
  nyra_ptr_listnode_destroy_func_t destroy;
} nyra_ptr_listnode_t;

NYRA_UTILS_API nyra_listnode_t *nyra_ptr_listnode_create(
    void *ptr, nyra_ptr_listnode_destroy_func_t destroy);

NYRA_UTILS_API nyra_ptr_listnode_t *nyra_listnode_to_ptr_listnode(
    nyra_listnode_t *self);

NYRA_UTILS_API nyra_listnode_t *nyra_listnode_from_ptr_listnode(
    nyra_ptr_listnode_t *self);

NYRA_UTILS_API void *nyra_ptr_listnode_get(nyra_listnode_t *self);

NYRA_UTILS_API void nyra_ptr_listnode_replace(
    nyra_listnode_t *self, void *ptr, nyra_ptr_listnode_destroy_func_t destroy);
