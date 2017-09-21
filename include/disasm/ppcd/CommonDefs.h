#pragma once

#ifdef  WIN32
#define WINDOWS
#endif

/*
 * General Data Types.
*/

typedef signed   char       s8;
typedef signed   short      s16;
typedef signed   long       s32;
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned long       u32;
typedef float               f32;
typedef double              f64;

#ifdef  WINDOWS
typedef unsigned __int64    u64;
typedef signed   __int64    s64;
#else
typedef unsigned long long  u64;
typedef signed   long long  s64;
#endif

#ifndef __cplusplus
//typedef enum { false = 0, true } bool;
#endif

#define FASTCALL    __fastcall
#define INLINE      __inline
