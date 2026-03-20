#include "../includes/memory.h"
#include <string.h>

// Variables initialization
//---------------------------
// Allocate memory (define globals once)

void memory_init(Memory *mem) {
    memset(mem->data, 0, MEMORY_SIZE);
}

uint8_t memory_read(Memory *mem, uint16_t addr) {
    return mem->data[addr];
}

void memory_write(Memory *mem, uint16_t addr, uint8_t value) {
    mem->data[addr] = value;
}
