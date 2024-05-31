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



extern uint32_t end;

void kmain(uint32_t magic, struct multiboot_info* bootInfo);

void kmain(uint32_t magic, struct multiboot_info* bootInfo) {

    print("Hello, World!\r\n");

    initIdt();  // Init Interrupt Descriptor Table and remap the PIC
    print("IDT: done!\r\n");

    InitializeCustomGDT();  // Init Global Descriptor Table
    print("GDT: done!\r\n");

    irq_install_handler(1, &keyboardHandler);
    print("Keyboard handler: done!\r\n");

    //init_scancode_to_ascii(); // Initialize the scancode to ASCII mapping
    //print("Scancode to ASCII mapping initialized.\r\n");

    // Initialize the kernel's memory manager using the end address of the kernel.
    init_kernel_memory(&end); // <- ASSIGNMENT

    // Initialize paging for memory management.
    init_paging(); // <- ASSIGNMENT
    //print("Paging: done!\r\n");

    // Print memory information.
    print_memory_layout(); // <- ASSIGNMENT
   // print("Memory layout: done!\r\n");

    // Initialize PIT
   // init_pit(); // <- ASSIGNMENT
   // print("PIT: done!\r\n");

    // Call the C++ main function of the kernel.
    return kernel_main();

    for(;;);

}