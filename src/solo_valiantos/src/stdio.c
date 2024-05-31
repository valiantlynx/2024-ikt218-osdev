#include "stdint.h"
#include "stdio.h"
#include "vga.h"
#include "stdarg.h"

#define VGA_WIDTH 80


void putc(char c)
{
    // Assuming print_char is a function that prints a single character on the screen.
    print_char(c);
}

void puts(const char *s)
{
    while (*s)
    {
        putc(*s++);
    }
}

static void print_number(unsigned int num, int base)
{
    char buffer[32];
    char *digits = "0123456789ABCDEF";
    int i = 0;

    if (num == 0)
    {
        putc('0');
        return;
    }

    while (num > 0)
    {
        buffer[i++] = digits[num % base];
        num /= base;
    }

    for (int j = i - 1; j >= 0; j--)
    {
        putc(buffer[j]);
    }
}

void printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    while (*fmt != '\0')
    {
        if (*fmt == '%')
        {
            fmt++; // Skip the '%'
            switch (*fmt)
            {
            case 'c':
            {                                      // Character
                char ch = (char)va_arg(args, int); // char is promoted to int
                putc(ch);
                break;
            }
            case 's':
            { // String
                const char *str = va_arg(args, const char *);
                puts(str);
                break;
            }
            case 'd':
            { // Signed decimal integer
                int num = va_arg(args, int);
                if (num < 0)
                {
                    putc('-');
                    num = -num;
                }
                print_number((unsigned int)num, 10);
                break;
            }
            case 'x':
            { // Unsigned hex integer
                unsigned int num = va_arg(args, unsigned int);
                print_number(num, 16);
                break;
            }
            case '%':
            { // Literal '%'
                putc('%');
                break;
            }
            }
        }
        else
        {
            putc(*fmt);
        }
        fmt++;
    }

    va_end(args);
}

/*
// Replace print_char with the actual function that writes a character to the VGA text mode buffer.
void print_char(char c)
{
    // Assuming `vga_buffer` is a pointer to the VGA text mode buffer
    // and `cursor_x` and `cursor_y` are the current coordinates on the screen.
    static uint16_t *vga_buffer = (uint16_t *)0xB8000;
    static uint16_t cursor_x = 0, cursor_y = 0;

    switch (c)
    {
    case '\n': // Newline characters
        cursor_x = 0;
        cursor_y++;
        break;
    case '\r': // Carriage return
        cursor_x = 0;
        break;
    default:                                                                          // Regular characters
        vga_buffer[cursor_y * VGA_WIDTH + cursor_x] = (uint16_t)c | (uint16_t)0x0700; // VGA entry: char + color attributes
        cursor_x++;
        break;
    }

    // Implement cursor wrapping or scrolling if needed
    if (cursor_x >= VGA_WIDTH)
    {
        cursor_x = 0;
        cursor_y++;
    }
}
*/

