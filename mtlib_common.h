#ifndef MTLIB_COMMON_H
#define MTLIB_COMMON_H

#include <stddef.h>
#include <stdint.h>

//! Macros
#define KB (1024ULL)
#define MB (KB * 1024)
#define GB (MB * 1024)
#define DEFAULT_ALIGNMENT (sizeof(void *) * 2)
#define is_power_of_two(x) (x != 0 && (x & (x - 1)) == 0)

#define bool  _Bool
#define false 0
#define true  1

#define local static
#define global static
#define function static

#define private static
#define public extern
#define c_link extern "C"
#define c_link_begin extern "C" {
#define c_link_end }

//! typedefs
typedef intptr_t isize;
typedef uintptr_t usize;

typedef uint8_t byte;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef int8_t  b8;
typedef int16_t b16;
typedef int32_t b32;
typedef int64_t b64;

typedef unsigned long ulong;
typedef unsigned int uint;
typedef uint8_t uchar;

typedef float f32;
typedef double f64;
typedef long double f128;

typedef struct common_allocator {
    void *(*alloc) (size_t size, void *context);
    void *(*free) (size_t size, void *ptr, void *context);
    void *context;
} Allocator;

#endif // MTLIB_COMMON_H