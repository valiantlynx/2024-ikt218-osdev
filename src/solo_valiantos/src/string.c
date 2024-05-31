#include "string.h"

size_t strlen(const char *str)
{
    const char *s;
    for (s = str; *s; ++s)
    {
    }
    return (s - str);
}

char *strcpy(char *dest, const char *src)
{
    char *temp = dest;
    while ((*dest++ = *src++) != '\0')
    {
    }
    return temp;
}

int strcmp(const char *str1, const char *str2)
{
    while (*str1 && (*str1 == *str2))
    {
        str1++, str2++;
    }
    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}
