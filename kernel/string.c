#include "string.h"

// Write len copies of val into dest.
// byte wise

void * memset(void *dest, int val, uint32_t len)
{
  uint8_t *temp = (uint8_t *)dest;
  for ( ; len != 0; len--) *temp++ = val;
}

void * memsetw(void *dest, int val, uint32_t len)
{
  uint16_t *temp = (uint16_t *)dest;
  for ( ; len != 0; len--) *temp++ = val;
}


void * memcpy(void *dest, const void *src, uint32_t len) {
	const uint8_t * sr = (const void *)src;
	uint8_t *temp = (uint8_t *)dest;
  for ( ; len != 0; len--) *temp++ = *sr++;
}

void * memcpyw(void *dest, const void *src, uint32_t len) {
  const uint16_t * sr = (const void *)src;
  uint16_t *temp = (uint16_t *)dest;
  for ( ; len != 0; len--) *temp++ = *sr++;
}
