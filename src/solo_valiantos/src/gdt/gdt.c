#include "gdt/gdt.h"

struct CustomGDTEntry gdtEntries[5];
struct CustomGDTPtr gdtPointer;

void InitCustomGDT() {
    gdtPointer.limit = (sizeof(struct CustomGDTEntry) * 5) - 1;
    gdtPointer.base = (uint32_t)&gdtEntries;

    // SEGMENTS
    // Null ...
    ConfigureCustomGDTEntry(0, 0, 0, 0, 0);
    // Kernel Code ...
    ConfigureCustomGDTEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    // Kernel Data ...
    ConfigureCustomGDTEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    // User Code ...
    ConfigureCustomGDTEntry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    // User Data ...
    ConfigureCustomGDTEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    // load the new gdt with asm
    GDTFlushCustom((uint32_t)&gdtPointer);
}

void ConfigureCustomGDTEntry(int gdtIndex, uint32_t segmentBase, uint32_t segmentLimit, uint8_t segmentAccess, uint8_t segmentGranularity) {
    gdtEntries[gdtIndex].baseLow = (segmentBase & 0xFFFF);
    gdtEntries[gdtIndex].baseMiddle = (segmentBase >> 16) & 0xFF;
    gdtEntries[gdtIndex].baseHigh = (segmentBase >> 24) & 0xFF;

    gdtEntries[gdtIndex].limitLow = (segmentLimit & 0xFFFF);
    gdtEntries[gdtIndex].granularity = ((segmentLimit >> 16) & 0x0F) | (segmentGranularity & 0xF0);
    gdtEntries[gdtIndex].access = segmentAccess;
}

extern void GDTFlushCustom(uint32_t gdtPointer){
    asm volatile("lgdt (%0)" : : "r" (gdtPointer));
    asm volatile("mov $0x10, %ax");
    asm volatile("mov %ax, %ds");
    asm volatile("mov %ax, %es");
    asm volatile("mov %ax, %fs");
    asm volatile("mov %ax, %gs");
    asm volatile("mov %ax, %ss");
    asm volatile("ljmp $0x08, $next");
    asm volatile("next:");
}
