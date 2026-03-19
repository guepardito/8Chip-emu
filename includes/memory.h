#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

// Memory management for the 8 Chip Emulator

// Variables declaration
// Memory
//---------------------------
#define MEMORY_SIZE 4096

extern uint8_t RAM_memory[MEMORY_SIZE];
//---------------------------

// Pointers
//---------------------------
extern uint16_t PC;
extern uint16_t I;
//---------------------------

// Stack
//---------------------------
#define STACK_SIZE 64
extern uint16_t stack[STACK_SIZE];
//---------------------------

// Timers
//---------------------------
extern uint8_t delay_timer;
extern uint8_t sound_timer;
//---------------------------

// Functions
void memory_init();

#endif // MEMORY_H