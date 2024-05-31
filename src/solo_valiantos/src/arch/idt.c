#include "idt.h"

struct IDTEntry idt[IDT_ENTRIES];
struct IDTPointer idtp;

void idtSetEntry(int n, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[n].base_lo = base & 0xFFFF;
    idt[n].base_hi = (base >> 16) & 0xFFFF;
    idt[n].sel = sel;
    idt[n].always0 = 0;
    idt[n].flags = flags;
}

extern void idt_load();

void initIDT() {
    idtp.limit = (sizeof(struct IDTEntry) * IDT_ENTRIES) - 1;
    idtp.base = (uint32_t)&idt;

    idt_load();
}
