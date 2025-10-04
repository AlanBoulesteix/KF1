; Declare constants for the multiboot header.
MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
MBFLAGS  equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + MBFLAGS)

section .multiboot
align 4
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM

section .bss
align 16
stack_bottom:
resb 16384 ; 16 KiB is reserved for stack
stack_top:

CODE_SEG equ 0x08
DATA_SEG equ 0x10

section .text
global _start:function (_start.end - _start)
_start:
    mov esp, stack_top

    cli
    extern init_gdt
    call init_gdt

    extern gdtr
    lgdt [gdtr]

    jmp CODE_SEG:.reload_CS  

.reload_CS:
    mov AX, DATA_SEG
    mov DS, AX
    mov ES, AX
    mov FS, AX
    mov GS, AX
    mov SS, AX


    extern PIC_init_protected
    call PIC_init_protected
    
    extern init_idt
    call init_idt 

    extern kernel_main
    call kernel_main

.hang:	hlt
    jmp .hang
.end:
