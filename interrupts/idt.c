#include "../include/idt.h"
#include "../include/pic.h"
#include "../include/print.h"
#include <stdint.h>

#include "../include/timer.h"

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_load(uint32_t); // implemented in assembly

// Forward declare IRQ assembly handlers
extern void irq0();
extern void irq1();

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

// A simple default exception handler
void fault_handler() {
    print_str("\n[EXCEPTION] Unhandled Exception occurred!\n");
    while(1);
}

void irq0_handler() {
    timer_handler();
    pic_send_eoi(0);
}

void idt_install() {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    // Clear IDT to zeros
    for (int i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    pic_remap();

    // Map IRQ1 (Keyboard) to IDT entry 33
    // 0x08 is the code segment selector in our simple GDT/boot setup
    // 0x8E is present, ring 0, 32-bit interrupt gate
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);

    // Map IRQ0 (Timer) to IDT entry 32 (Stub for Day 6)
    idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);

    idt_load((uint32_t)&idtp);
    
    // Enable interrupts
    __asm__ volatile("sti");
}
