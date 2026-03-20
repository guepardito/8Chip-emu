#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include "raylib.h"

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32 

extern uint8_t display_matrix[DISPLAY_WIDTH][DISPLAY_HEIGHT];
extern Image display_image;
extern Texture2D display_texture;

void display_clear(); // Clear the display by setting all pixels to 0, also
void display_init(); // Initialize the display
void display_draw(); // Draw the display matrix to the screen
int display_set_pixel(uint8_t x, uint8_t y, uint8_t value); // Set a pixel in the display matrix
void display_test(); // Test function to print the display matrix to the console


#endif // DISPLAY_H