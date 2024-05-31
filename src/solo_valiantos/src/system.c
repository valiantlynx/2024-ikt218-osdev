#include "stdio.h" // Assuming you use printf or any other standard I/O

void panic(const char *message)
{
    printf("Kernel Panic: %s\n", message);
    // Halt the CPU or loop indefinitely
    while (1)
    {
    }
}
