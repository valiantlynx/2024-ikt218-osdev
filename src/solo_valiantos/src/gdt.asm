global gdt_flush

gdt_flush:
    lgdt [esp+4]  ; load from the stack - gdt

    mov ax, 0x10 
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.flush

.flush:
    ret