#pragma once
#include <SDL.h>

typedef struct {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} color_t;

static color_t COLOR_RED = (color_t){255, 0, 0, 255};
static color_t COLOR_GREEN = (color_t){0, 255, 0, 255};
static color_t COLOR_BLUE = (color_t){0, 0, 255, 255};