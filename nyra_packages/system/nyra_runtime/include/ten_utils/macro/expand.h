//
// Copyright © 2024 Agora
// This file is part of NYRA Framework, an open source project.
// Licensed under the Apache License, Version 2.0, with certain conditions.
// Refer to the "LICENSE" file in the root directory for more information.
//
#pragma once

// clang-format off


#define NYRA_MACRO_ARGS_COUNT(...) \
  NYRA_MACRO_ARGS_COUNT_(_, ##__VA_ARGS__, NYRA_MACRO_PLACEHOLDERS())

#define NYRA_MACRO_PLACEHOLDERS()                                               \
    63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46,    \
    45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28,    \
    27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, \
    8, 7, 6, 5, 4, 3, 2, 1, 0

#define NYRA_MACRO_COUNT(                                                       \
    _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16,     \
    _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, \
    _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, \
    _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, \
    _62, _63, _64,  N, ...)                                                    \
  N

#define NYRA_MACRO_ARGS_COUNT_(...) NYRA_MACRO_COUNT(__VA_ARGS__)

#define NYRA_MACRO_CAR(...) NYRA_MACRO_CAR_(__VA_ARGS__)

#define NYRA_MACRO_CDR(...) NYRA_MACRO_CDR_(__VA_ARGS__)

#define NYRA_MACRO_CAR_(_1, ...) _1

#define NYRA_MACRO_CDR_(_1, ...) __VA_ARGS__

#define NYRA_MACRO_REPEAT(times, ...) NYRA_MACRO_REPEAT_##times(__VA_ARGS__)
#define NYRA_MACRO_REPEAT_1(...) __VA_ARGS__
#define NYRA_MACRO_REPEAT_2(...) NYRA_MACRO_REPEAT_1(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_3(...) NYRA_MACRO_REPEAT_2(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_4(...) NYRA_MACRO_REPEAT_3(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_5(...) NYRA_MACRO_REPEAT_4(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_6(...) NYRA_MACRO_REPEAT_5(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_7(...) NYRA_MACRO_REPEAT_6(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_8(...) NYRA_MACRO_REPEAT_7(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_9(...) NYRA_MACRO_REPEAT_8(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_10(...) NYRA_MACRO_REPEAT_9(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_11(...) NYRA_MACRO_REPEAT_10(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_12(...) NYRA_MACRO_REPEAT_11(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_13(...) NYRA_MACRO_REPEAT_12(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_14(...) NYRA_MACRO_REPEAT_13(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_15(...) NYRA_MACRO_REPEAT_14(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_16(...) NYRA_MACRO_REPEAT_15(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_17(...) NYRA_MACRO_REPEAT_16(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_18(...) NYRA_MACRO_REPEAT_17(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_19(...) NYRA_MACRO_REPEAT_18(__VA_ARGS__) __VA_ARGS__
#define NYRA_MACRO_REPEAT_20(...) NYRA_MACRO_REPEAT_19(__VA_ARGS__) __VA_ARGS__

// clang-format on
