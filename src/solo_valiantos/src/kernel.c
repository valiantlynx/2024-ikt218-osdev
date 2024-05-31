#include "vga.h"
#include "stdint.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "stdio.h"
#include "keyboard.h"
#include "multiboot2.h"
#include "util.h"
#include "memory.h"
#include "memutils.h"
#include "stdlib.h"
#include "stddef.h"
#include "memutils.h"
#include "memory.h"
#include "pit.h"
#include "string.h"
#include "interrupts.h"



extern uint32_t end;

void kernel_main(void);
void kmain(uint32_t magic, struct multiboot_info* bootInfo);

void kmain(uint32_t magic, struct multiboot_info *bootInfo)
{
    int counter = 0; // Declare the counter here


    initIdt(); // Initialize the Interrupt Descriptor Table and remap the PIC
    print("IDT is done!\r\n");

    InitializeCustomGDT(); // Initialize the Global Descriptor Table
    print("GDT is done!\r\n");

    irq_install_handler(1, &keyboardHandler);
    print("Keyboard handler is done!\r\n");

    init_kernel_memory(&end); // Initialize the kernel's memory manager
    print("Kernel memory initialization is done!\r\n");

    init_paging(); // Initialize paging for memory management
    print("Paging is done!\r\n");

    print_memory_layout(); // Print memory layout information
    print("Memory layout printing is done!\r\n");

    init_pit(); // Initialize PIT
    print("PIT is done!\r\n");

    // Call the C++ main function of the kernel.
    return kernel_main();

    for(;;);
}