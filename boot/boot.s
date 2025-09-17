.set ALIGN,    1<<0
.set MEMINFO,  1<<1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.set CODE_SEG, 0x08
.set DATA_SEG, 0x10

.section .text
.global _start
.type _start, @function
_start:
    mov $stack_top, %esp

    call init_gdt

	# Load GDT register
    lgdt [gdtr]

	# Far jump to reload CS
    ljmp $CODE_SEG, $.reload_CS  

.reload_CS:
    # Reload data segment registers:
    mov $DATA_SEG, %AX
    mov %AX, %DS
    mov %AX, %ES
    mov %AX, %FS
    mov %AX, %GS
    mov %AX, %SS

    call kernel_main

    cli
1:  hlt
    jmp 1b

.size _start, . - _start
