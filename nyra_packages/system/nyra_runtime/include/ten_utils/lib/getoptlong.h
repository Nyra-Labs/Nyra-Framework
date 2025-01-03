//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

typedef struct nyra_opt_long_t {
  const int short_name;
  const char *long_name;
  const int has_param;
  const char *help_msg;
} nyra_opt_long_t;

/**
 * @brief Print usage message
 * @param exec_name program name
 * @param opts option longs
 */
NYRA_UTILS_API void nyra_print_help(const char *exec_name,
                                  const nyra_opt_long_t *opts);

/**
 * @brief Parse command line arguments
 * @param argc argument count
 * @param argv argument values
 * @param opts option longs
 * @param p pointer to store parsed arguments
 * @return short name of the option, -1 if error
 */
NYRA_UTILS_API int nyra_getopt_long(int argc, const char **argv,
                                  const nyra_opt_long_t *opts, char **p);
