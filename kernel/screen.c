#include "screen.h"
#include "asmutil.h"

uint8_t cursor_x = 0;
uint8_t cursor_y = 0;
uint16_t *vram = (uint16_t *)0xb8000;
uint8_t char_attr = 0x07;

void screen_clear(void) {
  int loc = 0;
  for (;loc<24*80;loc++) {
    vram[loc] = 0 | char_attr << 8;
  }
}
void screen_set_char_attr(uint8_t a) {
	char_attr = a;
}

void screen_set_cursor_loc(uint8_t row, uint8_t col) {
	cursor_x = col;
	cursor_y = row;
}
void scroll(void) {}

void increment_cursor_y(void) {
  if (cursor_y >= 24) {scroll();}
  else {cursor_y++;}
}
void increment_cursor_x(void) {
  if (cursor_x >= 79) {
    cursor_x = 0;
    increment_cursor_y();
  } else {
    cursor_x++;
  }
}

void move_cursor(void) {
	uint16_t cursor_loc = cursor_x + cursor_y * 80;

	// following code copied from JamesM tutorial
	outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
  outb(0x3D5, cursor_loc >> 8); // Send the high cursor byte.
  outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
  outb(0x3D5, cursor_loc);      // Send the low cursor byte.
}


int screen_putc(uint8_t c) {
	uint16_t cursor_loc = cursor_x + cursor_y * 80;
	vram[cursor_loc] = c | char_attr << 8;
	increment_cursor_x();
  move_cursor();

	// TO-DO: write function to handle all forms of inputs
}

int screen_puts(const char * str) {
	int i = 0;
	while (str[i]) {
		screen_putc(str[i++]);
	}
}

// int screen_loc_putc(uint8_t c, uint8_t row, uint8_t col) {
// 	cursor_x = col;
// 	cursor_y = row;
// 	screen_putc(c);
// }
// int screen_loc_puts(const char * str, uint8_t row, uint8_t col) {
// 	cursor_x = col;
// 	cursor_y = row;
// 	screen_puts(str);
// }

