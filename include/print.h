#ifndef PRINT_H
#define PRINT_H

void terminal_init();
void clear_screen();
void print_char(char c);
void print_str(const char *msg);
void print_msg(const char *msg); // Alias for print_str for compatibility
void print_hex(unsigned int val);
void print_dec(int val);

#endif
