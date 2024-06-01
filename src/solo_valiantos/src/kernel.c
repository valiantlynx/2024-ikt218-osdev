#include "drivers/vga.h"
#include "libc/stdint.h"
#include "gdt/gdt.h"
#include "interrupts/idt/idt.h"
#include "interrupts/irq/timer.h"
#include "libc/stdio.h"
#include "drivers/keyboard.h"
#include "multiboot2.h"
#include "util.h"
#include "memory/memory.h"
#include "memory/memutils.h"
#include "libc/stdlib.h"
#include "libc/stddef.h"
#include "memory/memutils.h"
#include "memory/memory.h"
#include "interrupts/pit/pit.h"
#include "libc/string.h"
#include "interrupts/interrupts.h"



extern uint32_t end;

void kernel_main(void);
void kmain(uint32_t magic, struct multiboot_info* bootInfo);

void kmain(uint32_t magic, struct multiboot_info *bootInfo)
{
    int counter = 0; // Declare the counter here


    initIdt(); // and remap the PIC
    print("IDT: done!\r\n");

    InitCustomGDT();
    print("GDT: done!\r\n");

    irq_install_handler(1, &keyboardHandler);
    print("Keyboard handler: done!\r\n");

    init_kernel_memory(&end); // memory manager
    print("Kernel memory initialization: done!\r\n");

    init_paging(); // for memory management
    print("Paging: done!\r\n");

    print_memory_layout(); // memory layout information
    print("Memory layout printing: done!\r\n");

    init_pit();
    print("PIT: done!\r\n");

    // Call the C++ main function of the kernel.
    return kernel_main();

    for(;;);
}