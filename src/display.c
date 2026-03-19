#include <stdio.h>
#include "../includes/display.h"


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
}

void display_init() {
    display_clear();

    display_image = GenImageColor(DISPLAY_WIDTH, DISPLAY_HEIGHT, BLACK);
    display_texture = LoadTextureFromImage(display_image);

    SetTextureFilter(display_texture, TEXTURE_FILTER_POINT);
}

void display_draw() {
    for (int x = 0; x < DISPLAY_WIDTH; x++)
    {
        for (int y = 0; y < DISPLAY_HEIGHT; y++)
        {
            unsigned char* pixel = ((unsigned char*) display_image.data) + (y*DISPLAY_WIDTH + x) * 4;
            if (display_matrix[x][y] == 0)
            {
                SetPixelColor(pixel, BLACK, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
            } else {
                SetPixelColor(pixel, WHITE, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
            }
        }
        UpdateTexture(display_texture, display_image.data);
    }
}

void display_set_pixel(uint8_t x, uint8_t y, uint8_t value) {
    if (x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT) {
        fprintf(stderr, "Error: Pixel coordinates out of bounds (%d, %d)\n", x, y);
        return;
    }
    display_matrix[x][y] = value;
}

void display_test() {
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        for (int x = 0; x < DISPLAY_WIDTH; x++)
        {
            if (GetRandomValue(0, 1) < 0.5)
            {
                display_matrix[x][y] = 1;
            } else {
                display_matrix[x][y] = 0;
            }
        }
    }
}