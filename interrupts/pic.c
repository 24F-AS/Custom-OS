#include "../include/pic.h"
#include "../include/io.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

#define ICW1_INIT    0x10
#define ICW1_ICW4    0x01
#define ICW4_8086    0x01

void pic_remap() {
    unsigned char a1, a2;

    // Save masks
    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    // Start initialization sequence (in cascade mode)
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    // Set vector offsets (IRQs 0-7 mapped to 32-39, IRQs 8-15 mapped to 40-47)
    outb(PIC1_DATA, 0x20); // Master PIC offset
    outb(PIC2_DATA, 0x28); // Slave PIC offset

    // Setup cascading
    outb(PIC1_DATA, 4); // Tell Master there is a slave at IRQ2
    outb(PIC2_DATA, 2); // Tell Slave its cascade identity

    // Set 8086 mode
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    // Restore masks, but actually we should mask all except IRQ0 (Timer) and IRQ1 (Keyboard)
    // 0xFC = 11111100 in binary (masking IRQ 2-7)
    // 0xFF = 11111111 in binary (masking IRQ 8-15)
    outb(PIC1_DATA, 0xFC);
    outb(PIC2_DATA, 0xFF);
}

void pic_send_eoi(unsigned char irq) {
    if (irq >= 8) {
        outb(PIC2_COMMAND, 0x20);
    }
    outb(PIC1_COMMAND, 0x20);
}
