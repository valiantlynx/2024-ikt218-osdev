
#include "interrupts/irq/irq.h"
#include "interrupts/idt/idt.h"
#include "drivers/keyboard.h"


// Handler prototypes can be implemented in assembly and then call these C functions
void irq_handler_0() {
    // TODO: Handle timer interrupt
}

void irq_handler_1() {
    // TODO: Handle keyboard interrupt
}

void initialize_irq_handlers() {
    set_idt_entry(32, (unsigned long)irq0); // Remapped IRQ0
    set_idt_entry(33, (unsigned long)irq1); // Remapped IRQ1
    // TODO: Continue for other IRQs...
}

void initialize_irq_handlers() {
    // Register other IRQ handlers
    initialize_keyboard(); // This registers the keyboard handler for IRQ1
}