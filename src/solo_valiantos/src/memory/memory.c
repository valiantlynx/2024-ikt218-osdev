#include "libc/stdint.h"
#include "multiboot2.h"
#include "libc/stdio.h"
#include "util.h"
#include "memory/memory.h" 

static uint32_t *page_directory = 0; 
static uint32_t page_dir_loc = 0;  
static uint32_t *last_page = 0;

/* Paging now is simple
 * reserve 0-8MB for kernel stuff
 * heap will be from approx 1mb to 4mb
 * and paging stuff will be from 4mb
 */

void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys)
{
    uint16_t id = virt >> 22;      // Get the upper 10 bits of the virtual address. used as index in the page directory
    for (int i = 0; i < 1024; i++)
    {
        last_page[i] = phys | 3; 
        phys += 4096;  // 4 KB
    }
    page_directory[id] = ((uint32_t)last_page) | 3;         // Set the page directory entry for the virtual address to the physical address of the page table with present and write permissions set
    last_page = (uint32_t *)(((uint32_t)last_page) + 4096); // next
}

void paging_enable()
{
    asm volatile("mov %%eax, %%cr3" : : "a"(page_dir_loc)); // Load the physical address of the page directory into the CR3 register
    asm volatile("mov %cr0, %eax");                         // CR0 register into the EAX register
    asm volatile("orl $0x80000000, %eax");                  // paging enable bit in the EAX register
    asm volatile("mov %eax, %cr0");                         // EAX register into the CR0 register to enable paging
}

void init_paging()
{
    printf("Setting up paging\n");
    page_directory = (uint32_t *)0x400000;   //  4 MB
    page_dir_loc = (uint32_t)page_directory; // Set the physical address of the page directory
    last_page = (uint32_t *)0x404000;        // last page to start at 4 MB + 4 KB
    for (int i = 0; i < 1024; i++)        
    {
        page_directory[i] = 0 | 2; // Set the page directory entry to not present with supervisor level read/write permissions
    }
    paging_map_virtual_to_phys(0, 0);               // Map the first 4 MB of virtual memory to the first 4 MB of physical memory
    paging_map_virtual_to_phys(0x400000, 0x400000); // Map the next 4 MB of virtual memory to the next 4 MB of physical memory
    paging_enable();                                
    printf("Paging was successfully enabled!\n");
}
