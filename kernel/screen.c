#include "screen.h"
#include "asmutil.h"
#include "string.h"

uint8_t cursor_x = 0;
uint8_t cursor_y = 0;
uint16_t *vram = (uint16_t *)0xb8000;
uint8_t char_attr = 0x07;

// possible extension: buffer for text
// so that text reappears when scrolling up

void screen_clear(void) {
  int loc = 0;
  uint16_t val = ' ' | char_attr << 8;
  memsetw(vram, val, 80*25);

}
void screen_set_char_attr(uint8_t a) {
	char_attr = a;
}

void screen_set_cursor_loc(uint8_t row, uint8_t col) {
	cursor_x = col;
	cursor_y = row;
}

void decrement_cursor_y(void) {
  if (cursor_y) {cursor_y--;}
}

void decrement_cursor_x(void) {
  if (cursor_x) {
    cursor_x--;
  } else {
    cursor_x = 79;
    decrement_cursor_y();
  }
}

void scroll(void) {
  int len = 0;
  memcpyw(vram, vram+80, 24*80);
  memsetw(vram+24*80,' ' | char_attr << 8,80);
}


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

void new_line(void) {
  cursor_x = 0;
  increment_cursor_y();
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

  switch(c) {
    case '\b':
      decrement_cursor_x();
      vram[cursor_loc-1] = ' ' | char_attr << 8;
      break;
    case '\n':
      new_line();
      break;
    case '\t': // tab: not specified yet
      break;
    default:
      vram[cursor_loc] = c | char_attr << 8;
      increment_cursor_x();    
      break;
  }

  move_cursor();

	// TO-DO: write function to handle all forms of inputs
}

int screen_puts(const char * str) {
	int i = 0;
	while (str[i]) {
		screen_putc(str[i++]);
	}
}

int screen_putd(int n) {

  // adapted form JamesM's tutorial
  // added support for negative numbers

  if (n == 0)
  {
    screen_putc('0');
    return 0;
  }

  uint32_t neg = n & 0x8000;

  int acc; 
  if (neg) {
    acc = ~n + 1; // two's complement
  } else {
    acc = n;
  }

  char c[32]; // might not need that many
  int i = 0;
  while (acc > 0)
  {
      c[i] = '0' + acc%10;
      acc /= 10;
      i++;
  }
  c[i] = 0;

  char c2[32];
  c2[i--] = 0;
  int j = 0;
  while(i >= 0)
  {
      c2[i--] = c[j++];
  }
  if (neg) {
    screen_putc('-');
  }
  screen_puts(c2);

}

int screen_putx(uint32_t n) {

  uint8_t saved_attr = char_attr;
  screen_set_char_attr(0x70);

  screen_puts("0x");

  int temp;
  for (int i = 28; i >= 0; i -= 4) {
    temp = (n >> i) & 0xF;
    if (temp < 0xA) {
      screen_putc('0' + temp);
    } else {
      screen_putc('a' + (temp-0xA));
    }
  }
  screen_set_char_attr(saved_attr);
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

