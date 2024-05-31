#pragma once

#ifndef _STDDEF_H
#define _STDDEF_H

#define NULL ((void *)0)

// Define size_t based on your architecture
#if !defined(__size_t) && !defined(_SIZE_T_DEFINED)
#define __size_t
#define _SIZE_T_DEFINED

#if defined(_WIN64)
typedef unsigned __int64 size_t;
#elif defined(_WIN32)
typedef unsigned int size_t;
#else
// The following is typically accurate for most Unix-like systems
typedef unsigned long size_t;
#endif

#endif // !defined(__size_t) && !defined(_SIZE_T_DEFINED)

#endif // _STDDEF_H
