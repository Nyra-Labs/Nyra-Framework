//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
/* Modified from https://github.com/troydhanson/uthash. */
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdint.h>

typedef struct nyra_hashtable_t nyra_hashtable_t;
typedef struct nyra_hashhandle_t nyra_hashhandle_t;

struct nyra_hashhandle_t {
  nyra_hashtable_t *tbl;

  void *prev;  // previous hash handle in app-ordered list
  void *next;  // next hash handle in app-ordered list

  nyra_hashhandle_t *hh_prev;  // previous item in bucket
  nyra_hashhandle_t *hh_next;  // next item in bucket

  const void *key;   // ptr to key data
  uint32_t keylen;   // key len
  uint32_t hashval;  // result of hash function

  void (*destroy)(nyra_hashhandle_t *);
};

NYRA_UTILS_API void nyra_hashhandle_init(nyra_hashhandle_t *self,
                                       nyra_hashtable_t *table, const void *key,
                                       uint32_t keylen, void *destroy);

NYRA_UTILS_API void nyra_hashhandle_del_from_app_list(nyra_hashhandle_t *hh);
