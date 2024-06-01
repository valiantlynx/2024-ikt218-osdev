#include "interrupts/pit/pit.h"
#include "interrupts/isr/isr.h"
#include "interrupts/io/io.h"
#include "libc/stdio.h"

volatile uint32_t tick = 0; // Volatile to ensure changes are seen across all CPU cores and not cached

void pit_handler()
{
    tick++;
    onIrq0(); //  timer interrupt handler function
    outb(PIC1_CMD_PORT, PIC_EOI); // Acknowledge the interrupt at the PIC
}

#define PIT_BASE_FREQUENCY 1193182
#define TARGET_FREQUENCY 1000 // 1000 Hz or 1 ms per tick
#define DIVIDER (PIT_BASE_FREQUENCY / TARGET_FREQUENCY)

void init_pit()
{
    outb(PIT_CMD_PORT, 0x36);                       // Command byte for square wave mode
    outb(PIT_CHANNEL0_PORT, DIVIDER & 0xFF);        // Low byte
    outb(PIT_CHANNEL0_PORT, (DIVIDER >> 8) & 0xFF); // High byte
    register_interrupt_handler(IRQ0, &pit_handler); // IRQ0 is typically used for PIT
}

void sleep_busy(uint32_t milliseconds)
{
    uint32_t start_tick = tick;
    uint32_t ticks_to_wait = milliseconds; // Tick increments / ms
    while (tick - start_tick < ticks_to_wait)
    {
   
    }
}

void sleep_interrupt(uint32_t milliseconds)
{
    uint32_t end_tick = tick + milliseconds;
    while (tick < end_tick)
    {
        asm volatile("sti\n\t" // Enable interrupts
                     "hlt\n\t" // Halt CPU til next interrupt
                     ::: "memory");
    }
}

// current tick count of the PIT (for debugging or calibration)
uint16_t read_pit_count()
{
    outb(PIT_CMD_PORT, 0);                       // Latch command for channel 0
    uint16_t low_byte = inb(PIT_CHANNEL0_PORT);  // Read low byte
    uint16_t high_byte = inb(PIT_CHANNEL0_PORT); // Read high byte
    return (high_byte << 8) | low_byte;
}
