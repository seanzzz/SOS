#include "keyboard.h"
#include "isr.h"

static unsigned char kbdus[128] = // from Bran's tutorial; TO-DO: update keys
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};		

static unsigned char kbdus_shift[128] = // keys with shift
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', /* 9 */
  '(', ')', '_', '+', '\b', /* Backspace */
  '\t',     /* Tab */
  'Q', 'W', 'E', 'R', /* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', /* Enter key */
    0,      /* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', /* 39 */
 '\"', '~',   0,    /* Left shift */
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',      /* 49 */
  'M', '<', '>', '?',   0,        /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

uint8_t shift = 0;


void keyboard_callback(registers_t regs) {
  
  // screen_puts("recieved interrupt: ");
  unsigned char scancode;

  /* Read from the keyboard's data buffer */
  scancode = inb(0x60);

  if (scancode & 0x80) { // a key is released
    
    if (scancode == 0xAA || scancode == 0xB6) {
      // shift released
      shift = 0;
    }
  } else if (scancode == 0x2A || scancode == 0x36) {
    // shift pressed but yet released
    shift = 1;
  } else {
    // screen_putc(scancode);
    switch(scancode) {
      case 0x48:
        decrement_cursor_y();
        move_cursor();
        break;
      case 0x50:
        increment_cursor_y();
        move_cursor();
        break;
      case 0x4B:
        decrement_cursor_x();
        move_cursor();
        break;
      case 0x4D:
        increment_cursor_x();
        move_cursor();
        break;
      default:
        if (shift) {
          screen_putc(kbdus_shift[scancode]);
        } else {
          screen_putc(kbdus[scancode]);
        }
        break;
    }
  }

}

void init_keyboard(uint8_t keyboard_type) {
	// currently default to US
	// TO-DO: set keyboard to appropriate type

	register_interrupt_handler(IRQ1
		, &keyboard_callback);
}

