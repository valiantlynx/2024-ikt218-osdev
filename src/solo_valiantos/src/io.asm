; io.asm
global inb
global outb

section .text
inb:
    mov dx, [esp+4]
    in al, dx
    ret

outb:
    mov dx, [esp+4]
    mov al, [esp+8]
    out dx, al
    ret
