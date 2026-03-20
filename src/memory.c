#include "../includes/memory.h"
#include <string.h>
#include <stdio.h>

// Variables initialization
//---------------------------
unsigned char built_in_font[] = 
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

size_t built_in_font_len = 70;

void memory_init(Memory *mem) {
    memset(mem->data, 0, MEMORY_SIZE);
}

uint8_t memory_read(Memory *mem, uint16_t addr) {
    return mem->data[addr];
}

void memory_write(Memory *mem, uint16_t addr, uint8_t value) {
    mem->data[addr] = value;
}

void memory_built_in_font(Memory *mem) {
    for (size_t i = 0; i < built_in_font_len; i++)
    {
        uint16_t memory_position = 0x050 + i;
        memory_write(mem, memory_position, built_in_font[i]);
    }
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