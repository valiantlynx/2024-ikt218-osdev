#ifndef TIMER_H
#define TIMER_H

#include "stdint.h"
#include "interrupts.h" // Assuming this header defines InterruptRegisters

void initTimer();
void onIrq0(struct InterruptRegisters *regs);

#endif // TIMER_H
