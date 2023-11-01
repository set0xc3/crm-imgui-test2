#pragma once

// Base Types

#include <assert.h>
#include <memory.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <float.h>
#define REAL32_MAX FLT_MAX

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;

typedef i32 bool32;

#define global_variable static
#define local_variable  static
#define internal        static

#define Kilobytes(value) (value << 10)
#define Megabytes(value) (value << 20)
#define Gigabytes(value) ((u64)(value) << 30)
#define Terabytes(value) ((u64)(value) << 40)

#define ArrayCount(a) (sizeof((a)) / sizeof(*(a)))

#define Clamp(value, min, max)                                                \
  ((value <= min) ? min : (value >= max) ? max : value)
#define ClampTop(value, max) ((value >= max) ? max : value)

#define Align4(value)  ((value + 3) & ~3)
#define Align16(value) ((value + 15) & ~15)

#define TypeHasField(type, field)     (offsetof(type, field))
#define TypeFieldType(type, field)    (typeof(((type *)0)->field))
#define OffsetOfByString(type, field) ((size_t)(&((type *)0)->field))

// Platform Types

#ifdef __cplusplus
#define LANG_CPP
#endif

#ifdef __linux__
#define OS_LINUX
#else
#ifdef __WIN32__
#define OS_WINDOWS
#endif
#endif

#ifdef LANG_CPP
#ifdef OS_WINDOWS
#define exported extern "C" __declspec(dllexport)
#else
#define exported extern "C"
#endif
#else
#ifdef OS_WINDOWS
#define exported __declspec(dllexport)
#else
#define exported
#endif
#endif

#ifdef LANG_CPP
#ifdef OS_WINDOWS
#define imported extern "C" __declspec(dllimport)
#else
#define imported extern "C"
#endif
#else
#ifdef OS_WINDOWS
#define imported __declspec(dllimport)
#else
#define imported
#endif
#endif

#ifdef LANG_CPP
#define api extern "C"
#else
#define api
#endif

#ifdef LANG_CPP
#ifdef OS_WINDOWS
#ifdef exported
#define api extern "C" __declspec(dllexport)
#else
#define api extern "C" __declspec(dllimport)
#endif
#else
#define api extern "C"
#endif
#else
#ifdef OS_WINDOWS
#define api __declspec(dllexport)
#else
#define api
#endif
#endif
