// irq.h

#ifndef IRQ_H
#define IRQ_H

void initialize_irq_handlers(void);

// Define more as per your requirements
extern void irq0(); // Timer
extern void irq1(); // Keyboard

#endif
