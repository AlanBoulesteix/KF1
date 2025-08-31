FROM lfreydie/i386-elf-kfs

WORKDIR /workspace

RUN apt update && apt install -y \
    binutils \
    nasm \
    gcc g++ \
    libc6-dev \
    grub-pc-bin \
    grub-common \
    xorriso \
    elfutils \
    qemu-system && \
    rm -rf /var/lib/apt/lists/*

COPY . .

RUN bash ./scripts/create_iso.sh