#include "../include/print.h"

#define VGA_ADDRESS 0xB8000
#define VGA_COLS 80
#define VGA_ROWS 25

static unsigned short *vga_buffer = (unsigned short *)VGA_ADDRESS;
static int cursor_row = 0;
static int cursor_col = 0;
static unsigned char term_color = 0x0F; // White on black

void terminal_init() {
    clear_screen();
}

void clear_screen() {
    for (int i = 0; i < VGA_COLS * VGA_ROWS; i++) {
        vga_buffer[i] = (unsigned short)term_color << 8 | ' ';
    }
    cursor_row = 0;
    cursor_col = 0;
}

void print_char(char c) {
    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
    } else if (c == '\r') {
        cursor_col = 0;
    } else if (c == '\b') {
        if (cursor_col > 0) {
            cursor_col--;
        } else if (cursor_row > 0) {
            cursor_row--;
            cursor_col = VGA_COLS - 1;
        }
        int index = cursor_row * VGA_COLS + cursor_col;
        vga_buffer[index] = (unsigned short)term_color << 8 | ' ';
    } else {
        int index = cursor_row * VGA_COLS + cursor_col;
        vga_buffer[index] = (unsigned short)term_color << 8 | c;
        cursor_col++;
        if (cursor_col >= VGA_COLS) {
            cursor_col = 0;
            cursor_row++;
        }
    }
    
    // Simple scrolling
    if (cursor_row >= VGA_ROWS) {
        for (int j = 0; j < VGA_COLS * (VGA_ROWS - 1); j++) {
            vga_buffer[j] = vga_buffer[j + VGA_COLS];
        }
        for (int j = VGA_COLS * (VGA_ROWS - 1); j < VGA_COLS * VGA_ROWS; j++) {
            vga_buffer[j] = (unsigned short)term_color << 8 | ' ';
        }
        cursor_row = VGA_ROWS - 1;
    }
}

void print_str(const char *msg) {
    int i = 0;
    while (msg[i] != '\0') {
        print_char(msg[i]);
        i++;
    }
}

void print_msg(const char *msg) {
    print_str(msg);
}

void print_hex(unsigned int val) {
    print_str("0x");
    if (val == 0) {
        print_char('0');
        return;
    }
    
    char buffer[10]; // Enough for 8 hex digits
    int idx = 0;
    
    while (val > 0) {
        int rem = val % 16;
        if (rem < 10) buffer[idx++] = '0' + rem;
        else buffer[idx++] = 'A' + (rem - 10);
        val /= 16;
    }
    
    // Reverse and print
    for (int i = idx - 1; i >= 0; i--) {
        print_char(buffer[i]);
    }
}

void print_dec(int val) {
    if (val == 0) {
        print_char('0');
        return;
    }
    
    if (val < 0) {
        print_char('-');
        val = -val;
    }
    
    char buffer[12];
    int idx = 0;
    
    while (val > 0) {
        buffer[idx++] = '0' + (val % 10);
        val /= 10;
    }
    
    // Reverse and print
    for (int i = idx - 1; i >= 0; i--) {
        print_char(buffer[i]);
    }
}
