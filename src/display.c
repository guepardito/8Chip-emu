#include <stdio.h>
#include "../includes/display.h"
#include <string.h>

// (I should've made a Display struct, but for now it's not worth the time to refactor the display)

// Variables initialization
//---------------------------
// Allocate display matrix (define globals once)
uint8_t display_matrix[DISPLAY_WIDTH][DISPLAY_HEIGHT];
Image display_image;
Texture2D display_texture;

void display_clear() {
    for (uint16_t i = 0; i < DISPLAY_WIDTH; i++)
    {
        for (uint16_t j = 0; j < DISPLAY_HEIGHT; j++)
        {
            display_matrix[i][j] = 0;
        }
    }

    if (display_image.data != NULL) {
        memset(display_image.data, 0, DISPLAY_WIDTH * DISPLAY_HEIGHT * 4);
        UpdateTexture(display_texture, display_image.data);
    }
}

void display_init() {
    display_image = GenImageColor(DISPLAY_WIDTH, DISPLAY_HEIGHT, BLACK);
    display_texture = LoadTextureFromImage(display_image);

    SetTextureFilter(display_texture, TEXTURE_FILTER_POINT);

    display_clear();
}

void display_draw() {
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        for (int x = 0; x < DISPLAY_WIDTH; x++)
        {
            unsigned char* pixel = ((unsigned char*) display_image.data) + (y*DISPLAY_WIDTH + x) * 4;
            if (display_matrix[x][y] == 0)
            {
                SetPixelColor(pixel, BLACK, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
            } else {
                SetPixelColor(pixel, WHITE, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
            }
        }
    }
    UpdateTexture(display_texture, display_image.data);
}


int display_set_pixel(uint8_t x, uint8_t y, uint8_t value) {
    uint8_t old_pixel = display_matrix[x][y];
    display_matrix[x][y] ^= value;

    // Return 1 if a pixel was turned off (from 1 → 0), else 0
    return (old_pixel == 1 && display_matrix[x][y] == 0) ? 1 : 0;
}

void display_test() {
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        for (int x = 0; x < DISPLAY_WIDTH; x++)
        {
            display_matrix[x][y] = GetRandomValue(0,1);
        }
    }
}