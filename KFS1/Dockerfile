FROM rsabbah/x86-elf-gcc
WORKDIR /workspace


RUN apt update && apt upgrade -y
RUN apt install binutils -y
RUN apt install nasm -y
RUN apt install gcc g++ -y
RUN apt install libc6-dev -y
RUN apt install grub-pc-bin grub-common xorriso -y
RUN apt install elfutils -y
RUN apt install qemu-system -y

# Permet de compiler le fichier de boot
# RUN cd KFS && i686-elf-as boot.s -o boot.o

# Permet de compiler le fichier C
# i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

# Permet de linker boot.o et kernel.o
# i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

#mkdir -p isodir/boot/grub
#cp myos.bin isodir/boot/myos.bin
#cp grub.cfg isodir/boot/grub/grub.cfg

# Permet de generer un iso
#grub-mkrescue -o myos.iso isodir
