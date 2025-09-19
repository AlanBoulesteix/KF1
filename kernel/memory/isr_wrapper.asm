global isr_wrapper
align 4
bits 32
extern interrupt_handler

isr_wrapper:
    pusha
    cld    ; C code following the sysV ABI requires DF to be clear on function entry
    call interrupt_handler
    popa
    iret