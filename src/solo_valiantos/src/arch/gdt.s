; gdt.s file
global gdt_flush  ; GdtFlush globaly accessebel

section .text
gdt_flush:
    lgdt [esp+4]       
    mov ax, 0x10       
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush    

.flush:
    ret
