#ifndef KEYBOARD_H
#define KEYBOARD_H

#define INPUT_BUFFER_SIZE 256

void keyboard_init();
void keyboard_poll();
char* get_input_buffer();
void clear_input_buffer();

#endif
