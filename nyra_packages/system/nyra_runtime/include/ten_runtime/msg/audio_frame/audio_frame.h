//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_runtime/nyra_config.h"

#include <stddef.h>
#include <stdint.h>

#include "nyra_utils/lib/buf.h"
#include "nyra_utils/lib/error.h"
#include "nyra_utils/lib/smart_ptr.h"

// Note: To achieve the best compatibility, any new enum item, should be added
// to the end to avoid changing the value of previous enum items.
typedef enum NYRA_AUDIO_FRAME_DATA_FMT {
  NYRA_AUDIO_FRAME_DATA_FMT_INVALID,

  // Packet format in FFmpeg. Ex: ABABABAB
  NYRA_AUDIO_FRAME_DATA_FMT_INTERLEAVE,

  // Planar format in FFmpeg. Ex: AAAABBBB
  NYRA_AUDIO_FRAME_DATA_FMT_NON_INTERLEAVE,
} NYRA_AUDIO_FRAME_DATA_FMT;

typedef struct nyra_audio_frame_t nyra_audio_frame_t;

NYRA_RUNTIME_API nyra_shared_ptr_t *nyra_audio_frame_create(const char *name,
                                                         nyra_error_t *err);

NYRA_RUNTIME_API int64_t nyra_audio_frame_get_timestamp(nyra_shared_ptr_t *self);
NYRA_RUNTIME_API bool nyra_audio_frame_set_timestamp(nyra_shared_ptr_t *self,
                                                   int64_t timestamp);

NYRA_RUNTIME_API int32_t nyra_audio_frame_get_sample_rate(nyra_shared_ptr_t *self);
NYRA_RUNTIME_API bool nyra_audio_frame_set_sample_rate(nyra_shared_ptr_t *self,
                                                     int32_t sample_rate);

NYRA_RUNTIME_API uint64_t
nyra_audio_frame_get_channel_layout(nyra_shared_ptr_t *self);
NYRA_RUNTIME_API bool nyra_audio_frame_set_channel_layout(
    nyra_shared_ptr_t *self, uint64_t channel_layout);

NYRA_RUNTIME_API bool nyra_audio_frame_is_eof(nyra_shared_ptr_t *self);
NYRA_RUNTIME_API bool nyra_audio_frame_set_eof(nyra_shared_ptr_t *self,
                                             bool is_eof);

NYRA_RUNTIME_API int32_t
nyra_audio_frame_get_samples_per_channel(nyra_shared_ptr_t *self);
NYRA_RUNTIME_API bool nyra_audio_frame_set_samples_per_channel(
    nyra_shared_ptr_t *self, int32_t samples_per_channel);

NYRA_RUNTIME_API int32_t nyra_audio_frame_get_line_size(nyra_shared_ptr_t *self);
NYRA_RUNTIME_API bool nyra_audio_frame_set_line_size(nyra_shared_ptr_t *self,
                                                   int32_t line_size);

NYRA_RUNTIME_API int32_t
nyra_audio_frame_get_bytes_per_sample(nyra_shared_ptr_t *self);
NYRA_RUNTIME_API bool nyra_audio_frame_set_bytes_per_sample(
    nyra_shared_ptr_t *self, int32_t size);

NYRA_RUNTIME_API int32_t
nyra_audio_frame_get_number_of_channel(nyra_shared_ptr_t *self);
NYRA_RUNTIME_API bool nyra_audio_frame_set_number_of_channel(
    nyra_shared_ptr_t *self, int32_t number);

NYRA_RUNTIME_API NYRA_AUDIO_FRAME_DATA_FMT
nyra_audio_frame_get_data_fmt(nyra_shared_ptr_t *self);
NYRA_RUNTIME_API bool nyra_audio_frame_set_data_fmt(
    nyra_shared_ptr_t *self, NYRA_AUDIO_FRAME_DATA_FMT data_fmt);

NYRA_RUNTIME_API uint8_t *nyra_audio_frame_alloc_buf(nyra_shared_ptr_t *self,
                                                   size_t size);

NYRA_RUNTIME_API nyra_buf_t *nyra_audio_frame_peek_buf(nyra_shared_ptr_t *self);
