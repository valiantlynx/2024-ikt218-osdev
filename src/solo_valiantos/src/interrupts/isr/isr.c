#include "interrupts/isr/isr.h"
#include "interrupts/interrupts.h"
#include "libc/stdio.h"

isr_t interruptHandlers[256] = {0};

void register_interrupt_handler(uint8_t n, isr_t handler)
{
    interruptHandlers[n] = handler;
}

void isrHandler(registers_t *regs)
{
    if (interruptHandlers[regs->int_no] != 0)
    {
        isr_t handler = interruptHandlers[regs->int_no];
        handler(regs);
    }
    else
    {
        printf("Unhandled interrupt: %d\n", regs->int_no);
    }
}

// is called by your low-level assembly interrupt stubs.
void isr_handler_template(registers_t *regs)
{
    uint8_t int_no = regs->int_no;
    if (interruptHandlers[int_no])
    { //use interruptHandlers
        interruptHandlers[int_no](regs);
    }
}
