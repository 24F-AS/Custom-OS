#include "../include/timer.h"
#include "../include/io.h"
#include "../include/pic.h"

volatile uint32_t timer_ticks = 0;
static uint32_t timer_freq = 100; // Default 100 Hz

void timer_init(uint32_t frequency) {
    timer_freq = frequency;
    uint32_t divisor = 1193180 / frequency;

    // Send command byte (0x36) to PIT command port (0x43)
    // 0x36 = 00110110 in binary
    // Bits 6-7: Channel 0 (00)
    // Bits 4-5: Access mode (lobyte/hibyte) (11)
    // Bits 1-3: Operating mode 3 (Square wave generator) (011)
    // Bit 0: 16-bit binary (0)
    outb(0x43, 0x36);

    // Divisor must be sent byte by byte
    uint8_t l = (uint8_t)(divisor & 0xFF);
    uint8_t h = (uint8_t)((divisor >> 8) & 0xFF);

    // Send the frequency divisor to Channel 0 data port (0x40)
    outb(0x40, l);
    outb(0x40, h);
}

void timer_handler() {
    timer_ticks++;
    // We acknowledge the interrupt in irq0_handler in idt.c
}

uint32_t get_uptime() {
    return timer_ticks / timer_freq;
}
