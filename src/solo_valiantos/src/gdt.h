#include "stdint.h"

// Definerer en struktur for en GDT-oppføring
struct CustomGDTEntry {
    uint16_t limitLow;
    uint16_t baseLow;
    uint8_t baseMiddle;
    uint8_t access;
    uint8_t granularity;
    uint8_t baseHigh;
} __attribute__((packed));

// Definerer en struktur for GDT-pekeren
struct CustomGDTPtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// Funksjonsprototyper
void InitializeCustomGDT();
void ConfigureCustomGDTEntry(int gdtIndex, uint32_t segmentBase, uint32_t segmentLimit, uint8_t segmentAccess, uint8_t segmentGranularity);
extern void GDTFlushCustom(uint32_t gdtPointer);