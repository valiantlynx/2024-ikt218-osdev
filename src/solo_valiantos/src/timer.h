#ifndef TIMER_H
#define TIMER_H

#include "stdint.h"
#include "interrupts.h" // InterruptRegisters

void initTimer();
void onIrq0(struct InterruptRegisters *regs);

#endif
