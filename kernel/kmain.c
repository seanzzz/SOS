#include "common.h"
#include "descriptor_tables.h"
#include "timer.h"

void countNumbers() {
  short* vram = (short *)0xb8000;
  char* msg = "yo!";
  for (unsigned int i = 0; msg[i]; i++)
    vram[i+5] = msg[i] | '[' << 8;

  char* counter = "0000000000";

  for (int i = 9; i >= 0; i--)
    vram[i+80] = counter[i] | '[' << 8;  

  while (1) {
  counter[9]++;
  
    for (int i = 9; i >= 0; i--) {
      if (counter[i] == 0x3a) {
        // update screen
        counter[i] = 0x30;
        vram[i+80] = counter[i] | '[' << 8;  
        
        counter[i-1]++; // add to next
        vram[i+80-1] = counter[i-1] | '[' << 8;  
      } else {
        break;
      }
    }
  }
}
void kmain(void) {
  init_descriptor_tables();
  init_timer(50);
  __asm__ __volatile__ ("sti");

  countNumbers();
}
