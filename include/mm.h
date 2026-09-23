#ifndef MM_H
#define MM_H

#include <stdint.h>

void kheap_init(void *start, unsigned int size);
void *kmalloc(unsigned int size);
void get_memory_stats(uint32_t *total, uint32_t *used, uint32_t *free);

#endif
