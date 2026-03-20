#include "../includes/CPU.h"
#include "../includes/display.h"
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

    TraceLog(LOG_INFO, "Opened %s ROM", rom_path);

    // Set program counter to start of program
    cpu->PC = 0x200;
}


void cpu_cycle(CPU *cpu) {
    // Fetch instruction
    uint8_t first_byte = cpu->memory->data[cpu->PC];
    uint8_t second_byte = cpu->memory->data[cpu->PC+1];
    // TraceLog(LOG_INFO, "Instruction: %X %X", first_byte, second_byte);

    uint16_t opcode = (first_byte << 8) | second_byte;

    switch (opcode & 0xF000)
    {
        case 0x0000:
            switch (opcode)
            {
                case 0x00E0:
                    /* 
                    00E0 (Clean)
                    This is pretty simple: It should clear the display,
                    turning all pixels off to 0.
                    */
                    display_clear();
                    break;

                case 0x00EE:
                    /*
                    00EE (Returning from a subroutine)
                    Pops the last address from the stack and sets the PC to it.
                    */
                    break;
                
                default:
                    break;
            }
            break;
        
        case 0x1000:
            /* 
            1NNN (Jump)
            This instruction should simply set PC to NNN,
            causing the program to jump to that memory location.
            Do not increment the PC afterwards, it jumps directly there.
            */
            cpu->PC = opcode & 0x0FFF;
            break;

        case 0x6000: {
            /*
            6XNN (Set register VX)
            Simply set the register VX to the value NN.
            */
            uint8_t X = (opcode >> 8) & 0x0F;
            uint8_t NN = opcode & 0xFF;
            cpu->V[X] = NN;
            break;
        }
        
        case 0x7000: {
            /*
            7XNN (Add value to register VX)
            Add the value NN to VX.
            */
            uint8_t X = (opcode >> 8) & 0x0F;
            uint8_t NN = opcode & 0xFF;
            cpu->V[X] += NN;
            break;
        }

        case 0xA000: {
            /*
            ANNN (Set index)
            This sets the index register I to the value NNN.
            */
            uint16_t NNN = opcode & 0x0FFF;
            cpu->I = NNN;
            break;
        }

        case 0xD000: {
            /*
            AXYN (Display/draw)
            It will draw an N pixels tall sprite from the memory location
            that the I index register is holding to the screen,
            at the horizontal X coordinate in VX and the Y coordinate in VY.
            All the pixels that are “on” in the sprite will
            flip the pixels on the screen that it is drawn to
            (from left to right, from most to least significant bit).
            If any pixels on the screen were turned “off” by this,
            the VF flag register is set to 1. Otherwise, it’s set to 0.
            */
            uint8_t X = (opcode >> 8) & 0x0F;
            uint8_t Y = (opcode >> 4) & 0x0F;
            uint8_t N = opcode & 0x0F;

            uint8_t VX = cpu->V[X];
            uint8_t VY = cpu->V[Y];

            VX %= DISPLAY_WIDTH -1;
            VY %= DISPLAY_HEIGHT -1;

            cpu->VF = 0;

            for (uint8_t row = 0; row < N; row++)
            {
                uint8_t sprite_data = cpu->memory->data[cpu->I + row];
                for (uint8_t col = 0; col < 8; col++)
                {
                    if ((sprite_data & (0x80 >> col)) != 0)
                    {
                        if (display_set_pixel(VX + col, VY + row, 1)) {
                            cpu->VF = 1;
                        }
                    }
                    X++;
                }
                Y++;
                if (Y >= DISPLAY_HEIGHT) break;
            }
            
            break;
        }
            
        default:
            break;
    }
    
    // Move program counter to the next instruction
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