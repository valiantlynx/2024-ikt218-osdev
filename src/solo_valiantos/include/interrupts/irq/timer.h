#ifndef TIMER_H
#define TIMER_H

#include "libc/stdint.h"
#include "interrupts/interrupts.h" // InterruptRegisters

void initTimer();
void onIrq0(struct InterruptRegisters *regs);

#endif
