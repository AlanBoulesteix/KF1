# Building stage
FROM debian:bookworm AS builder

LABEL version="0.1"
LABEL description="This Dockerfile aims to build a compiler and a linker for the i386 architecture."

# Installer dépendances de build
RUN apt update && apt install -y \
    build-essential \
    bison \
    flex \
    libgmp3-dev \
    libmpc-dev \
    libmpfr-dev \
    texinfo \
    libisl-dev \
    wget && \
    rm -rf /var/lib/apt/lists/*

ENV PREFIX="/opt/cross" 
ENV TARGET=i386-elf 
ENV PATH="$PREFIX/bin:$PATH"

WORKDIR /tmp

# Installer binutils
RUN wget https://ftp.gnu.org/gnu/binutils/binutils-2.44.tar.gz && \
    tar -xf binutils-2.44.tar.gz && mkdir build-binutils && cd build-binutils && \
    ../binutils-2.44/configure --target=$TARGET --prefix=$PREFIX --disable-nls --disable-werror && \
    make -j$(nproc) && make install

# Installer gcc minimal
RUN wget https://ftp.gnu.org/gnu/gcc/gcc-15.2.0/gcc-15.2.0.tar.gz && \
    tar -xf gcc-15.2.0.tar.gz && mkdir build-gcc && cd build-gcc && \
    ../gcc-15.2.0/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c --without-headers && \
    make all-gcc -j$(nproc) && \
    make all-target-libgcc -j$(nproc) && \
    make install-gcc && make install-target-libgcc

# Final stage
FROM debian:bookworm
COPY --from=builder /opt/cross /opt/cross
ENV PATH="/opt/cross/bin:$PATH"

WORKDIR /src