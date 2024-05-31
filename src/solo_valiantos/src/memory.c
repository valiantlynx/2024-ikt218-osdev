#include "multiboot2.h"
#include "stdio.h"
#include "util.h"
#include "memory.h" // only once


#define NUM_PAGES_DIRS 256
#define NUM_PAGE_FRAMES (0x100000000 / 0x1000 / 8)

// Global variables as defined in memory.h
uint32_t physicalMemoryBitmap[NUM_PAGE_FRAMES / 8];
uint32_t initial_page_dir[1024];

static uint32_t pageFrameMin;
static uint32_t pageFrameMax;
static uint32_t totalAlloc;
static uint32_t pageDirs[NUM_PAGES_DIRS][1024] __attribute__((aligned(4096)));
static uint8_t pageDirUsed[NUM_PAGES_DIRS];
static uint32_t *page_directory = 0; // Pointer to the page directory
static uint32_t page_dir_loc = 0;    // Location of the page directory
static uint32_t *last_page = 0;      // Pointer to the last page

void pmm_init(uint32_t memLow, uint32_t memHigh)
{
    pageFrameMin = CEIL_DIV(memLow, 0x1000);
    pageFrameMax = memHigh / 0x1000;
    totalAlloc = 0;
    memset(physicalMemoryBitmap, 0, sizeof(physicalMemoryBitmap));
}

void initMemory(uint32_t memHigh, uint32_t physicalAllocStart)
{
    initial_page_dir[0] = 0;
    invalidate(0);
    initial_page_dir[1023] = ((uint32_t)initial_page_dir - KERNEL_START) | PAGE_FLAG_PRESENT | PAGE_FLAG_WRITE;
    invalidate(0xFFFFF000);
    pmm_init(physicalAllocStart, memHigh);
    memset(pageDirs, 0, sizeof(pageDirs));
    memset(pageDirUsed, 0, sizeof(pageDirUsed));
}

void invalidate(uint32_t vaddr)
{
    asm volatile("invlpg %0" ::"m"(vaddr));
}

void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys)
{
    uint16_t id = virt >> 22;
    for (int i = 0; i < 1024; i++)
    {
        last_page[i] = phys | 3; // Set present and write flags
        phys += 4096;            // Increment physical address by page size
    }
    page_directory[id] = ((uint32_t)last_page) | 3;
    last_page = (uint32_t *)((uint32_t)last_page + 4096);
}

void paging_enable()
{
    asm volatile("mov %%eax, %%cr3" : : "a"(page_dir_loc));
    asm volatile("mov %cr0, %eax");
    asm volatile("orl $0x80000000, %eax");
    asm volatile("mov %eax, %cr0");
}

void init_paging()
{
    printf("Setting up paging\n");
    page_directory = (uint32_t *)0x400000;   // Page directory at 4 MB
    page_dir_loc = (uint32_t)page_directory; // Physical address of directory
    last_page = (uint32_t *)0x404000;        // Start of page tables at 4 MB + 4 KB
    for (int i = 0; i < 1024; i++)
    {
        page_directory[i] = 0 | 2; // Supervisor level R/W, not present
    }
    paging_map_virtual_to_phys(0, 0);               // Map 0-4 MB of virtual to physical
    paging_map_virtual_to_phys(0x400000, 0x400000); // Map 4 MB - 8 MB of virtual to physical
    paging_enable();
    printf("Paging was successfully enabled!\n");
}