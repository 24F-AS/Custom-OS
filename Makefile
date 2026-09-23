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
BIN_DIR = bin

# Files
OBJS = $(BOOT_DIR)/boot.o \
       $(KERNEL_DIR)/kernel.o \
       $(DRIVERS_DIR)/print.o \
       $(KERNEL_DIR)/mm.o

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

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(BIN_DIR)

run: all
	qemu-system-i386 -kernel $(TARGET)
