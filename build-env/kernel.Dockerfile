FROM lfreydie/i386-elf-kfs

RUN apt update && apt install -y \
    binutils \
    nasm \
    gcc g++ \
    libc6-dev \
    grub-pc-bin \
    grub-common \
    xorriso \
    elfutils \
    make \
    qemu-system && \
    rm -rf /var/lib/apt/lists/*

VOLUME /workspace
WORKDIR /workspace