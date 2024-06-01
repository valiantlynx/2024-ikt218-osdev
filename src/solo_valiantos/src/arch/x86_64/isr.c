
#include "interrupts/isr/isr.h"
#include "terminal.h" // screen writing utility

void isr0() {
    terminal_write("Interrupt 0 (Divide by Zero) triggered\n");
}

void isr1() {
    terminal_write("Interrupt 1 (Keyboard Interrupt) triggered\n");
}

void isr2() {
    terminal_write("Interrupt 2 (Timer Interrupt) triggered\n");
}