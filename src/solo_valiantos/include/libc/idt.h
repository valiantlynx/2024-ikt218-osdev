#include "stdint.h"

#define IDT_ENTRIES 256

struct IDTEntry {
    uint16_t base_lo;    // Lower 16 bits of the interrupt handler address
    uint16_t sel;        // Kernel segment selector for this interrupt
    uint8_t always0;     // Must be zero
    uint8_t flags;       // Flags setting the type and attributes of the interrupt gate
    uint16_t base_hi;    // Upper 16 bits of the interrupt handler address
} __attribute__((packed));

struct IDTPointer {
    uint16_t limit;      // Size of the IDT in bytes minus 1
    uint32_t base;       // Address of the first element in the IDT
} __attribute__((packed));

void initIDT(void);
