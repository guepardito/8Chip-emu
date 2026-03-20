#include "../includes/CPU.h"
#include <stdio.h>
#include <string.h>
#include "raylib.h"

void cpu_init(CPU *cpu, Memory *mem) {
    // Initialize CPU state
    memset(cpu, 0, sizeof(CPU));
    cpu->memory = mem;
    cpu->PC = 0x200;
    cpu->sp = -1; // Stack pointer starts at -1 (empty stack)
}

void cpu_load_rom(CPU *cpu, const char *rom_path) {
    FILE* rom = fopen(rom_path, "rb");
    if (!rom)
    {
        TraceLog(LOG_ERROR, "Couldn't open the selected ROM\n");
        return;
    }
    
    // Move to the end of the file, get the size and return to beginning
    fseek(rom, 0, SEEK_END);
    size_t rom_size = ftell(rom);
    rewind(rom);

    if (rom_size > (MEMORY_SIZE - 0x200))
    {
        TraceLog(LOG_ERROR, "The selected ROM is too large to fit in memory\n");
        fclose(rom);
        return;
    }

    
    size_t bytes_read = fread(&cpu->memory->data[0x200], 1, rom_size, rom);
    if (bytes_read != rom_size) {
        TraceLog(LOG_ERROR, "The selected ROM couldn't load completely");
    }

    fclose(rom);

    // Set program counter to start of program
    cpu->PC = 0x200;
}


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