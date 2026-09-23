#include "../include/print.h"

#define VGA_ADDRESS 0xB8000
#define VGA_COLS 80
#define VGA_ROWS 25

static unsigned short *vga_buffer = (unsigned short *)VGA_ADDRESS;
static int cursor_row = 0;
static int cursor_col = 0;
static unsigned char term_color = 0x0F; // White on black

void clear_screen() {
    for (int i = 0; i < VGA_COLS * VGA_ROWS; i++) {
        vga_buffer[i] = (unsigned short)term_color << 8 | ' ';
    }
    cursor_row = 0;
    cursor_col = 0;
}

void print_msg(const char *msg) {
    int i = 0;
    while (msg[i] != '\0') {
        if (msg[i] == '\n') {
            cursor_row++;
            cursor_col = 0;
        } else {
            int index = cursor_row * VGA_COLS + cursor_col;
            vga_buffer[index] = (unsigned short)term_color << 8 | msg[i];
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
        i++;
    }
}
