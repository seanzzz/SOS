#ifndef STRING_H
#define STRING_H

#include <stdint.h>

void * memset(void *dest, int val, uint32_t len);
void * memcpy(void *dest, const void *src, uint32_t len);
int strcmp(char *str1, char *str2);
char *strcpy(char *dest, const char *src);

#endif