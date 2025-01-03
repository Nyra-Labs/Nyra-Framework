//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stddef.h>

#if !defined(NDEBUG)
  #define NYRA_SM_MAX_HISTORY 10
#else
  #define NYRA_SM_MAX_HISTORY 1
#endif

typedef struct nyra_sm_t nyra_sm_t;

typedef struct nyra_sm_state_history_t {
  int from;
  int event;
  int reason;
  int to;
} nyra_sm_state_history_t;

typedef void (*nyra_sm_op)(nyra_sm_t *sm, const nyra_sm_state_history_t *top,
                          void *arg);

#define NYRA_REASON_ANY (-1)

typedef struct nyra_sm_state_entry_t {
  int current;
  int event;
  int reason;
  int next;
  nyra_sm_op operation;
} nyra_sm_state_entry_t;

typedef struct nyra_sm_auto_trans_t {
  int from_state;
  int to_state;
  int auto_trigger;
  int trigger_reason;
} nyra_sm_auto_trans_t;

NYRA_UTILS_API nyra_sm_t *nyra_state_machine_create();

NYRA_UTILS_API void nyra_state_machine_destroy(nyra_sm_t *sm);

NYRA_UTILS_API int nyra_state_machine_init(nyra_sm_t *sm, int begin_state,
                                         nyra_sm_op default_op,
                                         const nyra_sm_state_entry_t *entries,
                                         size_t entry_count,
                                         const nyra_sm_auto_trans_t *trans,
                                         size_t trans_count);

NYRA_UTILS_API int nyra_state_machine_reset_state(nyra_sm_t *sm);

NYRA_UTILS_API int nyra_state_machine_trigger(nyra_sm_t *sm, int event, int reason,
                                            void *arg);

NYRA_UTILS_API int nyra_state_machine_current_state(const nyra_sm_t *sm);
