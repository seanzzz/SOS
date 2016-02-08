#include "string.h"

// Write len copies of val into dest.
void * memset(void *dest, int val, uint32_t len)
{
  uint8_t *temp = (uint8_t *)dest;
  for ( ; len != 0; len--) *temp++ = val;
}

void * memcpy(void *dest, const void *src, uint32_t len) {
	const uint8_t * sr = (const void *)src;
	uint8_t *temp = (uint8_t *)dest;
  for ( ; len != 0; len--) *temp++ = *sr++;
}

