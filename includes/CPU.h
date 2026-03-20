#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include "memory.h"

#define STACK_SIZE 32

typedef struct {
    Memory *memory; // Pointer to the memory structure

    uint8_t V[16]; // General-purpose registers V0 to VF
    uint16_t I; // Index register, point at locations in memory
    uint16_t PC; // Program counter

    uint16_t stack[STACK_SIZE]; // Stack for subroutine calls
    int8_t sp; // Stack pointer

    uint8_t delay_timer;
    uint8_t sound_timer;

    uint8_t VF;
} CPU;

void cpu_init(CPU *cpu, Memory *mem);
void cpu_load_rom(CPU *cpu, const char *rom_path);
void cpu_cycle(CPU *cpu);


#endif // CPU_H