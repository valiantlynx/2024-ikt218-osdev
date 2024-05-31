//
#ifndef MEMORY_H
#define MEMORY_H

#include "stdint.h"
#include "stddef.h"

// Declare the global variables but do not define them here
extern uint32_t physicalMemoryBitmap[];
extern uint32_t initial_page_dir[1024];

// Flags for page table entries
#define KERNEL_START 0xC0000000
#define PAGE_FLAG_PRESENT (1 << 0)
#define PAGE_FLAG_WRITE (1 << 1)

// Struct to represent memory allocations
typedef struct
{
    uint32_t status; // 0 for free, 1 for used
    uint32_t size;   // Size of the allocation
} alloc_t;

// Kernel memory initialization
void init_kernel_memory(uint32_t *kernel_end);

// Paging operations
void init_paging();                                            // Initializes paging
void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys); // Maps a virtual address to a physical address

// Memory allocation functions
char *pmalloc(size_t size); // Allocates memory with page alignment
void *malloc(size_t size);  // Allocates memory
void free(void *mem);       // Frees memory

// Memory manipulation functions
void *kmemcpy(void *dest, const void *src, size_t num); // Copies num bytes from src to dest
void *kmemset(void *ptr, int value, size_t num);        // Sets num bytes starting from ptr to value
void *kmemset16(void *ptr, uint16_t value, size_t num); // Sets num bytes starting from ptr to a 16-bit value

// Additional helper functions
void print_memory_layout(); // Prints the memory layout

#endif /* MEMORY_H */
