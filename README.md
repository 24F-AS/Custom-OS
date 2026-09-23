# Custom-OS

A minimal operating system with a custom bootloader that runs on QEMU. This project demonstrates fundamental OS development concepts including bootloader creation, kernel initialization, and low-level hardware interaction.

## 🚀 Features

- **Custom Bootloader**: Written in x86 Assembly to initialize the system
- **Basic Kernel**: C-based kernel with essential functionality
- **QEMU Compatible**: Designed to run on QEMU virtual machine
- **Educational Focus**: Perfect for learning OS development fundamentals

## 📋 Prerequisites

Before building and running Custom-OS, ensure you have the following installed:

- **NASM** (Netwide Assembler) - for assembling the bootloader
- **GCC** (GNU Compiler Collection) - for compiling the kernel
- **LD** (GNU Linker) - for linking object files
- **QEMU** - for running the OS in a virtual environment
- **Make** (optional) - for build automation

### Installation on Ubuntu/Debian

```bash
sudo apt update
sudo apt install nasm gcc qemu-system-x86 build-essential
```

### Installation on macOS

```bash
brew install nasm gcc qemu
```

## 🛠️ Building the Project

The project includes a build script that automates the compilation process:

```bash
chmod +x build.sh
./build.sh
```

### Manual Build Steps

If you prefer to build manually:

1. **Assemble the bootloader:**
   ```bash
   nasm -f elf32 boot.asm -o boot.o
   ```

2. **Compile the kernel:**
   ```bash
   gcc -m32 -c kernel.c -o kernel.o -ffreestanding -fno-pie
   ```

3. **Link the objects:**
   ```bash
   ld -m elf_i386 -T link.ld -o kernel.bin boot.o kernel.o
   ```

## ▶️ Running the OS

After building, run the OS with QEMU:

```bash
qemu-system-i386 -kernel kernel.bin
```

For additional debugging capabilities:

```bash
qemu-system-i386 -kernel kernel.bin -monitor stdio
```

## 📁 Project Structure

```
Custom-OS/
├── boot.asm        # Bootloader written in x86 Assembly
├── kernel.c        # Main kernel code in C
├── link.ld         # Linker script for memory layout
├── build.sh        # Build automation script
├── boot.o          # Compiled bootloader object file
├── kernel.o        # Compiled kernel object file
├── kernel.bin      # Final bootable kernel binary
└── README.md       # Project documentation
```

## 🔧 File Descriptions

- **boot.asm**: Contains the bootloader code that initializes the CPU and loads the kernel
- **kernel.c**: The main kernel implementation with core functionality
- **link.ld**: Defines memory layout and linking instructions
- **build.sh**: Automated build script that compiles all components

## 🎓 Learning Resources

This project is ideal for understanding:

- Bootloader development
- x86 Assembly programming
- Bare-metal C programming
- Memory management basics
- OS initialization process
- Cross-compilation techniques

## 🐛 Troubleshooting

### Common Issues

**Build fails with "command not found":**
- Ensure all prerequisites are installed correctly
- Check that NASM and GCC are in your PATH

**QEMU doesn't start:**
- Verify QEMU is installed: `qemu-system-i386 --version`
- Check that kernel.bin was created successfully

**Kernel doesn't boot:**
- Verify the linker script addresses are correct
- Check bootloader is properly loading the kernel

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.


---

**Note**: This is an educational project. It is not intended for production use.
