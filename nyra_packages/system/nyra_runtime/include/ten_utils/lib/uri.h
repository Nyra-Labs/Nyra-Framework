//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include "nyra_utils/lib/string.h"

#define NYRA_PROTOCOL_TCP "tcp"
#define NYRA_PROTOCOL_RAW "raw"
#define NYRA_PROTOCOL_PIPE "pipe"

typedef struct nyra_value_t nyra_value_t;

NYRA_UTILS_API nyra_string_t *nyra_uri_get_protocol(const char *uri);

NYRA_UTILS_API bool nyra_uri_is_protocol_equal(const char *uri,
                                             const char *protocol);

NYRA_UTILS_API nyra_string_t *nyra_uri_get_host(const char *uri);

NYRA_UTILS_API uint16_t nyra_uri_get_port(const char *uri);
