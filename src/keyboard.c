#include "../includes/keyboard.h"

#include "raylib.h"

uint16_t key_state = 0; // Each bit represents the state of a key (1 for pressed, 0 for released)

void keyboard_update() {
    // This function can be expanded to handle more keys and update the key_state variable accordingly.
    // For example, you can check for specific keys and set or clear bits in key_state based on their state.

    if (IsKeyDown(KEY_ONE)) {
        key_state |= 0x1; // Set bit 0 if key is pressed
    } else {
        key_state &= ~0x1; // Clear bit 0 if key is not pressed 
    }

    if (IsKeyDown(KEY_TWO)) {
        key_state |= 0x2;
    } else {
        key_state &= ~0x2;
    }

    if (IsKeyDown(KEY_THREE)) {
        key_state |= 0x3;
    } else {
        key_state &= ~0x3;
    }

    if (IsKeyDown(KEY_FOUR)) {
        key_state |= 0xC;
    } else {
        key_state &= ~0xC;
    }

    if (IsKeyDown(KEY_Q)) {
        key_state |= 0x4;
    } else {
        key_state &= ~0x4;
    }

    if (IsKeyDown(KEY_W)) {
        key_state |= 0x5;
    } else {
        key_state &= ~0x5;
    }

    if (IsKeyDown(KEY_E)) {
        key_state |= 0x6;
    } else {
        key_state &= ~0x6;
    }

    if (IsKeyDown(KEY_R)) {
        key_state |= 0xD;
    } else {
        key_state &= ~0xD;
    }

    if (IsKeyDown(KEY_A)) {
        key_state |= 0x7;
    } else {
        key_state &= ~0x7;
    }

    if (IsKeyDown(KEY_S)) {
        key_state |= 0x8;
    } else {
        key_state &= ~0x8;
    }

    if (IsKeyDown(KEY_D)) {
        key_state |= 0x9;
    } else {
        key_state &= ~0x9;
    }

    if (IsKeyDown(KEY_F)) {
        key_state |= 0xE;
    } else {
        key_state &= ~0xE;
    }

    if (IsKeyDown(KEY_Z)) {
        key_state |= 0xA;
    } else {
        key_state &= ~0xA;
    }

    if (IsKeyDown(KEY_X)) {
        key_state |= 0x0;
    } else {
        key_state &= ~0x0;
    }

    if (IsKeyDown(KEY_C)) {
        key_state |= 0xB;
    } else {
        key_state &= ~0xB;
    }

    if (IsKeyDown(KEY_V)) {
        key_state |= 0xF;
    } else {
        key_state &= ~0xF;
    }
}