#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

void screen_clear(void);
void screen_set_char_attr(uint8_t a);
void screen_set_cursor_loc(uint8_t row, uint8_t col);
int screen_putc(uint8_t c);
int screen_puts(const char * str);
int screen_putd(int n);
int screen_putx(uint32_t n);
// int screen_loc_putc(uint8_t c, uint8_t row, uint8_t col);
// int screen_loc_puts(const char * str, uint8_t row, uint8_t col);

#endif