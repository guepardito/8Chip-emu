#include <stdio.h>
#include "raylib.h"

#include "../includes/memory.h"
#include "../includes/display.h"
#include "../includes/keyboard.h"
#include "../includes/CPU.h"

int main(int argc, char *argv[]) {
    char* rom_path;
    // Check program arguments
    if (argc > 2) {
        fprintf(stderr, "Too Many arguments");
    } if (argc == 2) {
        rom_path = argv[1];
        printf("%s", rom_path);
    }

    // Initialization
    InitWindow(DISPLAY_WIDTH * 16, DISPLAY_HEIGHT * 16, "8 Chip Emulator");

    SetTargetFPS(60);

    // Create instances of CPU and Memory
    CPU cpu;
    Memory mem;

    cpu_init(&cpu, &mem);
    memory_init(&mem);
    display_init();

    // Instruction timing
    double chip8_ips = 700.0;
    double instruction_accumulator = 0.0;

    // Timer timing
    double timer_accumulator = 0.0;
    const double TIMER_STEP = 1.0 / 60.0; // 60Hz

    memory_built_in_font(&mem);

    cpu_load_rom(&cpu, rom_path);

    memory_dump_file(&mem, "mem_dump.dat");

    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        // Timing
        double dt = GetFrameTime();

        timer_accumulator += dt;
        instruction_accumulator += dt;

        double seconds_per_instruction = 1.0 / chip8_ips;

        while (instruction_accumulator >= seconds_per_instruction) {
            cpu_cycle(&cpu);
            instruction_accumulator -= seconds_per_instruction;
        }

        while (timer_accumulator >= TIMER_STEP) {
            // Update timers
            if (cpu.delay_timer > 0) {
                cpu.delay_timer--;
            }
            if (cpu.sound_timer > 0) {
                cpu.sound_timer--;
            }

            timer_accumulator -= TIMER_STEP;
        }
        //----------------------------------------------------------------------------------

        // Input handling
        //----------------------------------------------------------------------------------
            keyboard_update();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
            // display_test();
            display_draw();
            DrawTextureEx(display_texture, (Vector2){0, 0}, 0.0f, 16.0f, WHITE);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //----------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //----------------------------------------------------------------------------------
    
    return 0;
}