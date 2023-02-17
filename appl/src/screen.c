#include "screen.h"
#include <stdlib.h>
#include <string.h>

screen_t* screen_new(int w, int h, SDL_Renderer* r) {
    screen_t* screen = (screen_t*)malloc(sizeof(screen_t));
    screen->width = w;
    screen->height = h;
    screen->renderer = r;
    screen->texture = SDL_CreateTexture(r, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, w, h);
    screen->channels = 4;
    screen->color_buffer_size = w * h * screen->channels * sizeof(Uint8);
    screen->color_buffer = (Uint8*)malloc(screen->color_buffer_size); 
    screen->depth_buffer_size = w * h * sizeof(float);
    screen->depth_buffer = (float*)malloc(screen->depth_buffer_size);
    return screen;
}

void screen_free(screen_t* s) {
    SDL_DestroyTexture(s->texture);
    free(s->color_buffer);
    free(s->depth_buffer);
    free(s);
}

void screen_put_pixel(screen_t* screen, int x, int y, float z, color_t color) {
    if (x < 0 || x >= screen->width) return;
    if (y < 0 || y >= screen->height) return;

    int depth_index = y * screen->width + x;
    float prev_z = screen->depth_buffer[depth_index];
    if (prev_z > z) return;
    screen->depth_buffer[depth_index] = z;

    int index = (y * screen->width + x) * screen->channels;
    screen->color_buffer[index + 0] = color.r;
    screen->color_buffer[index + 1] = color.g;
    screen->color_buffer[index + 2] = color.b;
    screen->color_buffer[index + 3] = color.a;
}

void screen_blit(screen_t* screen) {
    SDL_UpdateTexture(screen->texture, NULL, screen->color_buffer, screen->width * screen->channels);
    SDL_RenderCopy(screen->renderer, screen->texture, NULL, NULL);
}

void screen_clear(screen_t* screen) {
    memset(screen->color_buffer, 0, screen->color_buffer_size);
    memset(screen->depth_buffer, 0xff, screen->depth_buffer_size);
}