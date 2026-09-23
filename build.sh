#!/bin/bash
set -e

mkdir -p bin

# Assemble bootloader
nasm -f elf32 boot/boot.asm -o boot/boot.o

# Compile C files
gcc -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-pie -c kernel/kernel.c -o kernel/kernel.o
gcc -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-pie -c drivers/print.c -o drivers/print.o
gcc -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-pie -c drivers/keyboard.c -o drivers/keyboard.o
gcc -m32 -I./include -ffreestanding -fno-stack-protector -fno-pic -fno-pie -c kernel/mm.c -o kernel/mm.o

# Link
ld -m elf_i386 -nostdlib -T link.ld -o bin/kernel.bin boot/boot.o kernel/kernel.o drivers/print.o drivers/keyboard.o kernel/mm.o

echo "Build successful! Run with: qemu-system-i386 -kernel bin/kernel.bin"
