// stdbool.h
#ifndef _STDBOOL_H_
#define _STDBOOL_H_

// Only define these for C, not for C++
#ifndef __cplusplus

// Check if the compiler supports _Bool
#if defined(__GNUC__) && !defined(__STRICT_ANSI__)
// Using _Bool type provided by GCC
typedef _Bool bool;
#define true 1
#define false 0
#else
// For compilers that do not support _Bool, define it manually as a char.
typedef char bool;
#define true 1
#define false 0
#endif

#endif // __cplusplus

#endif // _STDBOOL_H_
