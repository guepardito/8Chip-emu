#include "../includes/CPU.h"
#include <stdio.h>
#include <string.h>

void cpu_init(CPU *cpu, Memory *mem) {
    // Initialize CPU state
    memset(cpu, 0, sizeof(CPU));
    cpu->memory = mem;
    cpu->PC = 0x200;
    cpu->sp = -1; // Stack pointer starts at -1 (empty stack)
}

// void cpu_load_rom(CPU *cpu, const char *rom_path);


void cpu_cycle(CPU *cpu) {
    // Fetch instruction, move to the next instruction
    cpu->PC += 2;
}

// Stack operations
int stack_push(CPU *cpu, uint16_t value) {
    if (!(cpu->sp < -1) && cpu->sp+1 < STACK_SIZE)
    {
        cpu->sp++;
        cpu->stack[cpu->sp] = value;
        return 0;
    }
    return -1;
}

uint16_t stack_pop(CPU *cpu) {
    if (!(cpu->sp < -1) && cpu->sp < STACK_SIZE+1)
    {
        cpu->sp--;
        uint16_t value = cpu->stack[cpu->sp];
        return value;
    }
    return -1;
}