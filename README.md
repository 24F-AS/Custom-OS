# MinOS - Lightweight Educational Operating System

MinOS is a 32-bit x86 custom operating system built from scratch. It avoids over-engineering in favor of clean, readable code to demonstrate core operating system concepts.

## Features

- **Custom Boot & Kernel Entry**: Boots via Multiboot (GRUB/QEMU) into protected mode assembly and jumps directly to `kernel_main()` in C.
- **VGA Terminal & Keyboard Driver**: Full hardware abstraction for the VGA buffer and PS/2 Keyboard controller via `inb`/`outb` polling and interrupts.
- **Interrupts (IDT & PIC)**: Features a fully configured Interrupt Descriptor Table and a remapped Programmable Interrupt Controller handling hardware IRQs cleanly.
- **System Timer (PIT)**: The Programmable Interval Timer is configured to fire at 100 Hz, maintaining a precise kernel tick counter.
- **Preemptive Round-Robin Scheduler**: Timer-driven context switching. The CPU halts gracefully, and upon every PIT interrupt, it transparently switches CPU registers and stacks between running tasks.
- **Memory Management**: Basic kernel heap allocation (`kmalloc`) with runtime memory statistics tracking.
- **Interactive Shell**: Type commands live! Supports:
  - `help`: Command list
  - `clear`: Clears VGA screen
  - `echo`: Repeats input
  - `mem`: Shows dynamic heap statistics
  - `tasks`: Lists active background tasks
  - `uptime`: Calculates live runtime from PIT ticks
  - `crash`: Intentionally triggers a CPU exception to demonstrate IDT fault handling

## Architecture

```text
Boot / Multiboot Entry (boot.asm)
          ↓
Kernel Initialization (kernel.c)
          ↓
IDT + Interrupt Handling (idt.c)
          ↓
PIC Configuration + PIT Timer (100 Hz)
          ↓
Preemptive Round-Robin Scheduler (scheduler.c)
          ↓
VGA Terminal + PS/2 Keyboard IRQ
          ↓
Interactive Shell (shell.c)
```

## How to Build and Run

1. Ensure you have `gcc`, `nasm`, `ld`, and `qemu-system-i386` installed.
2. Run the build script or Makefile:
```bash
make
# or 
./build.sh
```
3. The OS will automatically launch in QEMU!

## Project Layout

- `boot/`: Multiboot headers and assembly entry point.
- `kernel/`: Core kernel logic, scheduler, memory manager, and string utilities.
- `drivers/`: VGA terminal and keyboard interface.
- `interrupts/`: IDT, PIC remapping, and assembly ISR stubs.
- `shell/`: Interactive command-line environment.
- `include/`: C header files.
