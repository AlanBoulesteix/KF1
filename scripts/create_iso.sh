#!/bin/bash

boot_dir=boot
kernel_dir=kernel
iso_dir=isodir/boot

# Permet de compiler le fichier de boot
i386-elf-as $boot_dir/boot.s -o $boot_dir/boot.o

# Permet de compiler le fichier C
i386-elf-gcc -c $kernel_dir/kernel.c -o $kernel_dir/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -fno-builtin -fno-stack-protector -nostdlib -nodefaultlibs

# Permet de linker boot.o et kernel.o
i386-elf-gcc -T $boot_dir/linker.ld -o $boot_dir/myos.bin -ffreestanding -nostdlib -nodefaultlibs $boot_dir/boot.o $kernel_dir/kernel.o -lgcc

mkdir -p $iso_dir/grub
cp $boot_dir/myos.bin $iso_dir/myos.bin
cp $boot_dir/grub.cfg $iso_dir/grub/grub.cfg

# Permet de generer un iso
grub-mkrescue -o myos.iso $iso_dir
