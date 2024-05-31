#ifndef STDLIB_H
#define STDLIB_H

#include "stddef.h" // For size_t

#ifdef __cplusplus
extern "C"
{
#endif

    void free(void *ptr);

    // Declaration for malloc
    void *malloc(size_t size);

#ifdef __cplusplus
}
#endif

#endif // MY_KERNEL_STDLIB_H
