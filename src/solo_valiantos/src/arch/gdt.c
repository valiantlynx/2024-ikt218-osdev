#include "gdt.h"

#define GDT_SIZE 5

struct GDTEntry gdt[GDT_SIZE];

struct GDTPointer gp;

extern void GDTflush(uint32_t);


void initGDT(void) {
    
    gp.limit = (sizeof(struct GDTEntry) * GDT_SIZE) - 1;
    gp.base = (uint32_t)&gdt;

  
    setGDTEntry(0, 0, 0, 0, 0);
  
    setGDTEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  
    setGDTEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
   
    setGDTEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
   
    setGDTEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    gdt_flush((uint32_t)&gp);
}

void setGDTEntry(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[index].base_low = (base & 0xFFFF);
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;

    gdt[index].limit_low = (limit & 0xFFFF);
    gdt[index].granularity = ((limit >> 16) & 0x0F);

    gdt[index].granularity |= (granularity & 0xF0);
    gdt[index].access = access;
}
