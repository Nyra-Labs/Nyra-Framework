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

#include "nyra_utils/container/list_node.h"
#include "nyra_utils/lib/signature.h"
#include "nyra_utils/lib/string.h"

#define NYRA_STR_LISTNODE_SIGNATURE 0x15D33B50C27A1B20U

typedef struct nyra_str_listnode_t {
  nyra_listnode_t hdr;
  nyra_signature_t signature;
  nyra_string_t str;
} nyra_str_listnode_t;

NYRA_UTILS_API nyra_listnode_t *nyra_str_listnode_create(const char *str);

NYRA_UTILS_API nyra_listnode_t *nyra_str_listnode_create_with_size(const char *str,
                                                                size_t size);

NYRA_UTILS_API nyra_str_listnode_t *nyra_listnode_to_str_listnode(
    nyra_listnode_t *self);

NYRA_UTILS_API nyra_listnode_t *nyra_listnode_from_str_listnode(
    nyra_str_listnode_t *self);

NYRA_UTILS_API nyra_string_t *nyra_str_listnode_get(nyra_listnode_t *self);
