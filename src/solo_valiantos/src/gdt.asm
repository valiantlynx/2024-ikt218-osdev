global gdt_flush

gdt_flush:
    lgdt [esp+4]  ; Laster basen av GDT fra stakken

    mov ax, 0x10  ; 0x10 er offseten til data segmentet i GDT
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
;print "Global Descriptor Table initialized.\n
;print ""
    jmp 0x08:.flush  ; 0x08 er offseten til kode segmentet i GDT

.flush:
    ret