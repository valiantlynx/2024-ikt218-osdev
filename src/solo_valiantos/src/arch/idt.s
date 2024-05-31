global idt_load
section .text
idt_load:
    lidt [esp+4] ; the IDT pointer structure loaded
    ret
