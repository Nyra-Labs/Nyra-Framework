//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

#include "nyra_utils/nyra_config.h"

#include <jni.h>

/**
 * @brief: Enable jni
 * @param jvm: Java VM object
 */
NYRA_UTILS_API void nyra_jni_enable(JavaVM *jvm);

/**
 * @brief: Attach to current thread and fetch jni env
 * @return: jni env object of current thread, nullptr if jni not enabled
 * @note: You can assume this function always return valid jni env
 *        if |nyra_jni_enable| already called.
 *        Will automatically detach when thread destroying
 */
NYRA_UTILS_API JNIEnv *nyra_jni_attach_current_thread();
