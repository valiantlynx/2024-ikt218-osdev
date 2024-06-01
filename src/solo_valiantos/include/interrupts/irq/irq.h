
#ifndef IRQ_H
#define IRQ_H

void initialize_irq_handlers(void);

extern void irq0(); // Timer
extern void irq1(); // Keyboard
// TODO: more ...

#endif
