#ifndef STDIO_H
#define STDIO_H

#include "stdbool.h"

void putc(char c);
void puts(const char *str);
void printf(const char *fmt, ...);
int *printf_number(int *, int, bool, int);

#include "stdint.h"

extern void x86_div64_32(uint64_t, uint32_t, uint64_t *, uint32_t *);

#define PRINTF_STATE_START 0
#define PRINTF_STATE_LENGTH 1
	@@ -16,3 +23,5 @@ extern void x86_div64_32(uint64_t, uint32_t, uint64_t*, uint32_t*);
#define PRINTF_LENGTH_SHORT 2
#define PRINTF_LENGTH_LONG 3
#define PRINTF_LENGTH_LONG_LONG 4

#endif 