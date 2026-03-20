#include "../includes/memory.h"
#include <string.h>
#include <stdio.h>

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

void memory_dump_file(Memory *mem, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("Failed to open file for memory dump");
        return;
    }

    for (uint16_t i = 0; i < MEMORY_SIZE; i++) {
        if (i % 16 == 0) {
            fprintf(f, "\n%04X: ", i);
        }
        fprintf(f, "%02X ", mem->data[i]);
    }

    fprintf(f, "\n");
    fclose(f);
}