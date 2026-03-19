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
extern int8_t stack_pointer;
//---------------------------

// Timers
//---------------------------
extern uint8_t delay_timer;
extern uint8_t sound_timer;
extern float timer_accumulator;
const float TIMER_STEP = 1.0f / 60.0f;
//---------------------------

// Functions
void memory_init();

// Stack operations
int stack_push(uint16_t value);
uint16_t stack_pop();

#endif // MEMORY_H