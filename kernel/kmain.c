#include "string.h"
// #include "asmutil.h"
#include "descriptor_tables.h"
#include "time.h"
#include "screen.h"
#include "keyboard.h"

void count_numbers() {
  
  screen_clear();
  screen_set_char_attr(0x07);
  char* welcome_msg = "Hello! Welcome to SOS, Sean's Operating System.";
  // char* counter = "0000000000";
  screen_puts(welcome_msg);

  // for (int i = 9; i >= 0; i--)
  //   vram[i+80] = counter[i] | '[' << 8;  

  // while (1) {
  // counter[9]++;
  
  //   for (int i = 9; i >= 0; i--) {
  //     if (counter[i] == 0x3a) {
  //       // update screen
  //       counter[i] = 0x30;
  //       vram[i+80] = counter[i] | '[' << 8;  
        
  //       counter[i-1]++; // add to next
  //       vram[i+80-1] = counter[i-1] | '[' << 8;  
  //     } else {
  //       break;
  //     }
  //   }
  // }
}
void kmain(void) {
  init_descriptor_tables();
  init_timer(50);
  init_keyboard(0);
  __asm__ __volatile__ ("sti");

  count_numbers();
}
