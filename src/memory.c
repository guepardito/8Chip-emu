#include "../includes/memory.h"

// Variables initialization
//---------------------------
// Allocate memory (define globals once)
uint8_t RAM_memory[MEMORY_SIZE];

uint16_t PC;
uint16_t I;

uint16_t stack[STACK_SIZE];
int8_t stack_pointer;

uint8_t delay_timer;
uint8_t sound_timer;

float timer_accumulator = 0.0f;


void memory_init() {
    // Memory
    for (int i = 0; i < MEMORY_SIZE; i++) {
        RAM_memory[i] = 0;
    }

    int fontset[80] = {
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

    int start_address = 0x050;

    for (int i = 0; i < 80; i++) {
        RAM_memory[start_address + i] = fontset[i];
    }

    // Pointers
    PC = 0x200; // Program counter starts at 0x200
    I = 0;

    // Stack
    stack_pointer = -1;

    // Timers
    delay_timer = 0;
    sound_timer = 0;
}

// Stack operations
int stack_push(uint16_t value) {
    if (!(stack_pointer < -1) && stack_pointer+1 < STACK_SIZE)
    {
        stack_pointer++;
        stack[stack_pointer] = value;
        return 0;
    }
    return -1;
}

uint16_t stack_pop() {
    if (!(stack_pointer < -1) && stack_pointer < STACK_SIZE+1)
    {
        stack_pointer--;
        uint16_t value = stack[stack_pointer];
        return value;
    }
    return -1;
}