#!/bin/bash
set -e

mkdir -p bin

# Assemble assembly files
nasm -f elf32 boot/boot.asm -o boot/boot.o
nasm -f elf32 interrupts/interrupts.asm -o interrupts/interrupts.o

# Compile C files
gcc -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-pie -c kernel/kernel.c -o kernel/kernel.o
gcc -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-pie -c drivers/print.c -o drivers/print.o
gcc -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-pie -c drivers/keyboard.c -o drivers/keyboard.o
gcc -m32 -I./include -ffreestanding -fno-stack-protector -fno-pic -fno-pie -c kernel/mm.c -o kernel/mm.o
gcc -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-pie -c kernel/string.c -o kernel/string.o
gcc -m32 -I./include -ffreestanding -fno-stack-protector -fno-pic -fno-pie -c kernel/timer.c -o kernel/timer.o
gcc -m32 -I./include -ffreestanding -fno-stack-protector -fno-pic -fno-pie -c shell/shell.c -o shell/shell.o
gcc -m32 -I./include -ffreestanding -fno-stack-protector -fno-pic -fno-pie -c interrupts/idt.c -o interrupts/idt.o
gcc -m32 -I./include -ffreestanding -fno-stack-protector -fno-pic -fno-pie -c interrupts/pic.c -o interrupts/pic.o

# Link
ld -m elf_i386 -nostdlib -T link.ld -o bin/kernel.bin boot/boot.o interrupts/interrupts.o kernel/kernel.o drivers/print.o drivers/keyboard.o kernel/mm.o kernel/string.o kernel/timer.o shell/shell.o interrupts/idt.o interrupts/pic.o

echo "Build successful! Run with: qemu-system-i386 -kernel bin/kernel.bin"
