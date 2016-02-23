#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>

uint32_t malloc(uint32_t sz);

/* page aligned */
uint32_t malloc_a(uint32_t sz);

/* page aligned, physical address is returned */
uint32_t malloc_ap(uint32_t sz, uint32_t *phys);

#endif