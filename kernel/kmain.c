#include "string.h"
// #include "asmutil.h"
#include "descriptor_tables.h"
#include "time.h"
#include "screen.h"
#include "keyboard.h"

void welcome() {
  
  char* welcome_msg = "Hello! Welcome to SOS, Sean's Operating System.\n";
  screen_puts(welcome_msg);
  screen_puts("This is a hex number:");
  screen_putx(256);
  screen_putc('\n');

}
void kmain(void) {
  init_descriptor_tables();
  init_keyboard(0);
  screen_clear();
  screen_set_char_attr(0x07);
  welcome();
  init_timer(10);
  __asm__ __volatile__ ("sti");

  // begin user process here...
  while (1) {}
}
