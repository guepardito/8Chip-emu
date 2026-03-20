#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

// Memory management for the 8 Chip Emulator

// Variables declaration
// Memory
//---------------------------
#define MEMORY_SIZE 4096

typedef struct {
    uint8_t data[MEMORY_SIZE];
} Memory;
//---------------------------

// Functions
void memory_init(Memory *mem);
uint8_t memory_read(Memory *mem, uint16_t addr);
void memory_write(Memory *mem, uint16_t addr, uint8_t value);
void memory_dump_file(Memory *mem, const char *filename);

#endif // MEMORY_H