#ifndef STRING_H
#define STRING_H

#include "stddef.h" // For size_t

// Implementations of standard string functions
size_t strlen(const char *str);
char *strcpy(char *dest, const char *src);
int strcmp(const char *str1, const char *str2);

// Number to string conversion functions
char *itoa(int value, char *str, int base);

#endif // STRING_H
