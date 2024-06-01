#include "libc/stdio.h"

void panic(const char *message)
{
    printf("Kernel Panic: %s\n", message);
    // Halt the CPU or loop indefinitely
    while (1)
    {
    }
}
