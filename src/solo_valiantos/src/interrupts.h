#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "stdint.h"

// registers_t is defined in isr.h
#include "isr.h"

typedef void (*isr_t)(registers_t *); // ISR handler type

extern isr_t interruptHandlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler);
void isrHandler(registers_t *regs);

#endif
