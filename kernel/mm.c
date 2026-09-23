#include "../include/mm.h"
#include <stdint.h>

static uint32_t heap_start = 0;
static uint32_t heap_size = 0;
static uint32_t current_heap_ptr = 0;

void kheap_init(void *start, unsigned int size) {
    heap_start = (uint32_t)start;
    heap_size = size;
    current_heap_ptr = heap_start;
}

void *kmalloc(unsigned int size) {
    if (size == 0) return 0;
    
    // Align to 4 bytes
    if (size % 4 != 0) {
        size += 4 - (size % 4);
    }
    
    if (current_heap_ptr + size > heap_start + heap_size) {
        return 0; // Out of memory
    }
    
    void *ptr = (void *)current_heap_ptr;
    current_heap_ptr += size;
    return ptr;
}
