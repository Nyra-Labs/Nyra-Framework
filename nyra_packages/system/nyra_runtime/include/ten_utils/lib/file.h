//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "nyra_utils/lib/buf.h"

typedef struct nyra_string_t nyra_string_t;

NYRA_UTILS_API int nyra_file_remove(const char *filename);

NYRA_UTILS_API int nyra_file_size(const char *filename);

NYRA_UTILS_API char *nyra_file_read(const char *filename);

NYRA_UTILS_API char *nyra_symlink_file_read(const char *path);

NYRA_UTILS_API int nyra_file_write(const char *filename, nyra_buf_t buf);

NYRA_UTILS_API int nyra_file_write_to_open_file(FILE *fp, nyra_buf_t buf);

NYRA_UTILS_API int nyra_file_clear_open_file_content(FILE *fp);

NYRA_UTILS_API int nyra_file_copy(const char *src_filename,
                                const char *dest_filename);

NYRA_UTILS_API int nyra_file_copy_to_dir(const char *src_file,
                                       const char *dest_dir);

NYRA_UTILS_API int nyra_symlink_file_copy(const char *src_file,
                                        const char *dest_file);

NYRA_UTILS_API int nyra_file_get_fd(FILE *fp);

NYRA_UTILS_API int nyra_file_chmod(const char *filename, uint32_t mode);

NYRA_UTILS_API int nyra_file_clone_permission(const char *src_filename,
                                            const char *dest_filename);

NYRA_UTILS_API int nyra_file_clone_permission_by_fd(int src_fd, int dest_fd);

/**
 * @brief Open a file for reading.
 *
 * @param does_not_exist If @a does_not_exist is not NULL, @a *does_not_exist
 * will be set to false normally and set to true if the file does not exist. If
 * the file does not exist and @a does_not_exist is not NULL, the function will
 * return -1.
 *
 * @return -1 on error.
 */
NYRA_UTILS_API int nyra_file_open(const char *filename, bool *does_not_exist);

/**
 * @brief Close a file opened by nyra_file_open().
 *
 * @return true on success, false on error.
 */
NYRA_UTILS_API bool nyra_file_close(int fd);
