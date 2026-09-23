CC = gcc
CFLAGS = -m32 -ffreestanding -fno-stack-protector -fno-pic -fno-pie -I./include
LD = ld
LDFLAGS = -m elf_i386 -nostdlib -T link.ld
AS = nasm
ASFLAGS = -f elf32

# Directories
BOOT_DIR = boot
KERNEL_DIR = kernel
DRIVERS_DIR = drivers
SHELL_DIR = shell
INT_DIR = interrupts
BIN_DIR = bin

# Files
OBJS = $(BOOT_DIR)/boot.o \
       $(INT_DIR)/interrupts.o \
       $(KERNEL_DIR)/kernel.o \
       $(DRIVERS_DIR)/print.o \
       $(DRIVERS_DIR)/keyboard.o \
       $(KERNEL_DIR)/mm.o \
       $(KERNEL_DIR)/string.o \
       $(KERNEL_DIR)/timer.o \
       $(KERNEL_DIR)/scheduler.o \
       $(SHELL_DIR)/shell.o \
       $(INT_DIR)/idt.o \
       $(INT_DIR)/pic.o

TARGET = $(BIN_DIR)/kernel.bin

.PHONY: all clean run

all: $(BIN_DIR) $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

$(BOOT_DIR)/%.o: $(BOOT_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

$(KERNEL_DIR)/%.o: $(KERNEL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DRIVERS_DIR)/%.o: $(DRIVERS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(SHELL_DIR)/%.o: $(SHELL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(INT_DIR)/%.o: $(INT_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(INT_DIR)/%.o: $(INT_DIR)/%.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(BIN_DIR)

run: all
	qemu-system-i386 -kernel $(TARGET)
