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

NYRA_UTILS_API void nyra_list_push_str_back(nyra_list_t *self, const char *str);

NYRA_UTILS_API void nyra_list_push_str_front(nyra_list_t *self, const char *str);

NYRA_UTILS_API void nyra_list_push_str_with_size_back(nyra_list_t *self,
                                                    const char *str,
                                                    size_t size);

NYRA_UTILS_API nyra_listnode_t *nyra_list_find_string(nyra_list_t *self,
                                                   const char *str);
