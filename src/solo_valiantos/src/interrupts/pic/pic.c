#pragma once
#include "libc/stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

// since we are operating on the x86 architecture, we have two PICs (cascade mode)

#define MASTER_PIC_COMMAND_PORT     0x20    // command port for master PIC
#define MASTER_PIC_DATA_PORT        0x21    // data port for master PIC
#define SLAVE_PIC_COMMAND_PORT      0xA0    // command port for slave PIC
#define SLAVE_PIC_DATA_PORT         0xA1    // data port for slave PIC

#define PIC_EOI                     0x20    // end of interrupt command
#define PIC_READ_IRR                0x0A    // read interrupt request register command
#define PIC_READ_ISR                0x0B    // read in-service register command


/* Control Word 1   
// first bit is for the pic to expect ICW4 (Initialization Control Word 4) 
// second bit is for single mode (only one pic) or cascade mode (two pics)
// third bit is for the pic to expect a call address interval of 4 (or 8)
// fourth bit is for the pic to be in level triggered mode (or edge triggered mode)
// fifth bit is for the pic to be initialized (1)
// bit six to eight are ignored on x86 architecture (set to 0)
*/
#define PIC_ICW4(x)                 (x << 0x00)    // ICW4 1 is needed (0 is not needed)
#define PIC_SINGLE(x)               (x << 0x01)    // cascade mode (0) or single mode (1)
#define PIC_INTERVAL4(x)            (x << 0x02)    // call address interval of 4 (0) or 8 (1)
#define PIC_LEVEL(x)                (x << 0x03)    // level triggered mode (1) or edge triggered mode (0)
#define PIC_INIT(x)                 (x << 0x04)    // initialization - required! (1)


/* Control Word 4
// first bit tells if the pic is in 8086/8088 mode (1) or MCS-80/85 mode (0)
// second bit tells if the pic is in automatic end of interrupt mode (1) or normal EOI mode (0)
// third bit tells if the pic is the master (1) or the slave (0)
// fourth bit tells if the pic is in buffer mode (1) or non-buffer mode (0)
// fifth bit tells if the pic is in special fully nested mode (1) or not (0)
// bit six to eight are reserved (set to 0)
*/
#define PIC_8086(x)                 (x << 0x00)    // 8086/8088 mode (1) or MCS-80/85 mode (0)
#define PIC_AEOI(x)                 (x << 0x01)    // automatic end of interrupt (1) or normal EOI (0)
#define PIC_MASTER(x)               (x << 0x02)    // master (1) or slave (0)
#define PIC_BUFFERRED(x)            (x << 0x03)    // buffer mode (1) or non-buffer mode (0)
#define PIC_SFNM(x)                 (x << 0x04)    // special fully nested mode (1) or not (0)

//
void initialize_pic(uint8_t master_offset, uint8_t slave_offset);
void end_of_interrupt(int irqNum);

void DisablePic();
void mask_pic(int irqNum);
void unmask_pic(int irqNum);
uint16_t RetrieveIRQRegisters();
uint16_t RetrieveISRRegisters();

#ifdef __cplusplus
}
#endif