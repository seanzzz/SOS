// implements common.h

#include "common.h"

void outb(u16int port, u8int value) {
	__asm__ __volatile__("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
   u8int ret;
   __asm__ __volatile__("inb %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

u16int inw(u16int port)
{
   u16int ret;
   __asm__ __volatile__ ("inw %1, %0" : "=a" (ret) : "dN" (port));
   return ret;
}

// Write len copies of val into dest.
void memset(u8int *dest, u8int val, u32int len)
{
    u8int *temp = (u8int *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}