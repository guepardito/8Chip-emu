#include <stdio.h>
#include "raylib.h"

#include "../includes/memory.h"
#include "../includes/display.h"

int main() {
    // Initialization
    InitWindow(DISPLAY_WIDTH * 16, DISPLAY_HEIGHT * 16, "8 Chip Emulator");

    SetTargetFPS(60);

    memory_init();
    display_init();

    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        timer_accumulator += GetFrameTime();

        while (timer_accumulator >= TIMER_STEP) {
            // Update timers
            if (delay_timer > 0) {
                delay_timer--;
            }
            if (sound_timer > 0) {
                sound_timer--;
            }

            timer_accumulator -= TIMER_STEP;
        }
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