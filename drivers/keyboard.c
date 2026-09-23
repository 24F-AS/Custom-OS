#include "../include/keyboard.h"
#include "../include/io.h"
#include "../include/print.h"

static char input_buffer[INPUT_BUFFER_SIZE];
static int buffer_index = 0;
static int shift_pressed = 0;

// Simple PS/2 Set 1 Scancode to ASCII map (lowercase)
const char scancode_to_ascii[] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-',
    0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

// Shifted map
const char scancode_to_ascii_shift[] = {
    0, 27, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-',
    0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void keyboard_init() {
    buffer_index = 0;
    shift_pressed = 0;
    for (int i = 0; i < INPUT_BUFFER_SIZE; i++) {
        input_buffer[i] = '\0';
    }
}

void clear_input_buffer() {
    buffer_index = 0;
    for (int i = 0; i < INPUT_BUFFER_SIZE; i++) {
        input_buffer[i] = '\0';
    }
}

char* get_input_buffer() {
    return input_buffer;
}

void keyboard_poll() {
    // Check if data is available in the PS/2 controller (bit 0 of status register 0x64)
    if (inb(0x64) & 0x01) {
        unsigned char scancode = inb(0x60);
        
        // Handle Shift keys
        if (scancode == 0x2A || scancode == 0x36) {
            shift_pressed = 1;
            return;
        } else if (scancode == 0xAA || scancode == 0xB6) {
            shift_pressed = 0;
            return;
        }

        // Only process key presses (scancode < 0x80)
        if (scancode < 0x80) {
            char c = shift_pressed ? scancode_to_ascii_shift[scancode] : scancode_to_ascii[scancode];
            
            if (c != 0) {
                if (c == '\b') {
                    // Backspace
                    if (buffer_index > 0) {
                        buffer_index--;
                        input_buffer[buffer_index] = '\0';
                        
                        // We also need to erase it visually from the terminal. 
                        // Our print_char doesn't support backspace yet, let's implement basic visual backspace
                        // by moving cursor back, printing space, moving back again.
                        // For a clean terminal driver, we should add backspace logic to print_char.
                        print_char('\b');
                    }
                } else if (c == '\n') {
                    // Enter key
                    print_char('\n');
                    // We just leave the buffer as is so the shell can read it.
                    // The shell will process it and then call clear_input_buffer()
                } else {
                    // Normal character
                    if (buffer_index < INPUT_BUFFER_SIZE - 1) {
                        input_buffer[buffer_index++] = c;
                        input_buffer[buffer_index] = '\0';
                        print_char(c);
                    }
                }
            }
        }
    }
}
