//
// isr.h -- Interface and structures for high level interrupt service routines.
// Part of this code is modified from Bran's kernel development tutorials.
// Rewritten for JamesM's kernel development tutorials.
//

#ifndef ISR_H
#define ISR_H

#include "stdint.h"


// Registers struct pushed by pusha and by interrupt handlers
typedef struct registers
{
   uint32_t ds;                                     // Data segment selector
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
   uint32_t int_no, err_code;                       // Interrupt number and error code (if applicable)
   uint32_t eip, cs, eflags, useresp, ss;           // Pushed by the processor automatically.
} registers_t;

// Definitions for IRQ numbers after remapping the PIC
#define IRQ0 0x20  // Timer interrupt
#define IRQ1 0x21  // Keyboard interrupt
#define IRQ2 0x22  // Cascade signal from PIC2 to PIC1
#define IRQ3 0x23  // COM2 (if enabled)
#define IRQ4 0x24  // COM1 (if enabled)
#define IRQ5 0x25  // LPT2 (if enabled)
#define IRQ6 0x26  // Floppy disk
#define IRQ7 0x27  // LPT1 / Unreliable "spurious" interrupt (usually)
#define IRQ8 0x28  // CMOS real-time clock (if enabled)
#define IRQ9 0x29  // Free for peripherals / legacy SCSI / NIC
#define IRQ10 0x2A // Free for peripherals / SCSI / NIC
#define IRQ11 0x2B // Free for peripherals / SCSI / NIC
#define IRQ12 0x2C // PS2 Mouse
#define IRQ13 0x2D // FPU / Coprocessor / Inter-processor
#define IRQ14 0x2E // Primary ATA Hard Disk
#define IRQ15 0x2F // Secondary ATA Hard Disk

// Function prototype for ISR and IRQ handlers
typedef void (*isr_t)(registers_t*); // Function pointer type for handlers
void register_interrupt_handler(uint8_t n, isr_t handler);

#endif // ISR_H
