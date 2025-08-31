#!/bin/bash

# Permet de compiler le fichier de boot
i386-elf-as boot.s -o boot.o

# Permet de compiler le fichier C
i386-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

# Permet de linker boot.o et kernel.o
i386-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

mkdir -p isodir/boot/grub
cp myos.bin isodir/boot/myos.bin
cp grub.cfg isodir/boot/grub/grub.cfg

# Permet de generer un iso
grub-mkrescue -o myos.iso isodir
