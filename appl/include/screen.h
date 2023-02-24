#pragma once
#include <SDL.h>
#include "color.h"

typedef struct {
    int width;
    int height;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    Uint8* color_buffer;
    size_t color_buffer_size;
    int channels;
    float* depth_buffer;
    size_t depth_buffer_size;
} screen_t;

screen_t* screen_new(int w, int h, SDL_Renderer* r);
void screen_free(screen_t* s);
void screen_put_pixel(screen_t* screen, int x, int y, float z, color_t color);
void screen_blit(screen_t* screen);
void screen_clear(screen_t* screen);
void screen_clear_color(screen_t* screen, color_t* color);