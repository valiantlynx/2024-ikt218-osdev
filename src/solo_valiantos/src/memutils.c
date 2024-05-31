//memutils.c
#include "memutils.h"

void *kmemcpy(void *dest, const void *src, size_t count)
{
    char *dst8 = (char *)dest;
    const char *src8 = (const char *)src;

    while (count--)
    {
        *dst8++ = *src8++;
    }

    return dest;
}

void *kmemset(void *ptr, int value, size_t num)
{
    unsigned char *p = (unsigned char *)ptr;
    while (num--)
    {
        *p++ = (unsigned char)value;
    }
    return ptr;
}

void *kmemset16(void *ptr, uint16_t value, size_t num)
{
    uint16_t *p = (uint16_t *)ptr;
    while (num--)
    {
        *p++ = value;
    }
    return ptr;
}
