#ifndef MEMUTILS_H
#define MEMUTILS_H

#include "libc/stdlib.h"
#include "libc/stdint.h"

void *kmemcpy(void *dest, const void *src, size_t count);
void *kmemset(void *ptr, int value, size_t num);
void *memset16(void *ptr, uint16_t value, size_t num);

#endif
