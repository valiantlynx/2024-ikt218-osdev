#ifndef STDLIB_H
#define STDLIB_H

#include "libc/stddef.h" // size_t

#ifdef __cplusplus
extern "C"
{
#endif

    void free(void *ptr);
    void *malloc(size_t size);

#ifdef __cplusplus
}
#endif

#endif
