#include "string.h"
// #include "asmutil.h"
#include "descriptor_tables.h"
#include "time.h"
#include "screen.h"
#include "keyboard.h"

void welcome() {
  
  char* welcome_msg = "Hello! Welcome to SOS, Sean's Operating System.";
  screen_puts(welcome_msg);
  screen_putx(256);

}
void kmain(void) {
  init_descriptor_tables();
  init_timer(10);
  init_keyboard(0);
  screen_clear();
  screen_set_char_attr(0x07);

  __asm__ __volatile__ ("sti");

  welcome();
}
