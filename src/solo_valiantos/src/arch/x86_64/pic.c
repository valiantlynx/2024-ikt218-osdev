
#include "interrupts/pic/pic.h"
#include "interrupts/io/io.h" // this contains outb and inb functions

#define PIC1         0x20
#define PIC2         0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA    (PIC1+1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA    (PIC2+1)

void PIC_remap(int offset1, int offset2) {
    unsigned char a1, a2;

    a1 = inb(PIC1_DATA); // Save masks
    a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, 0x11); // initialization in cascade mode
    outb(PIC2_COMMAND, 0x11);
    outb(PIC1_DATA, offset1); // ICW2: Master PIC vector offset
    outb(PIC2_DATA, offset2); // ICW2: Slave PIC vector offset
    outb(PIC1_DATA, 0x04); // ICW3: Tell Master PIC there's a slave at IRQ2
    outb(PIC2_DATA, 0x02); // ICW3: Tell Slave PIC its cascade identity
    outb(PIC1_DATA, 0x01); // ICW4: 8086 mode
    outb(PIC2_DATA, 0x01);
    outb(PIC1_DATA, a1); // Restore saved masks
    outb(PIC2_DATA, a2);
}