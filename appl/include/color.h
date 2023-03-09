#pragma once
#include <SDL.h>

typedef struct
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} color_t;

color_t color_mult(color_t* color, float scalar);
color_t color_add(color_t* c1, color_t* c2);
color_t color_clamp(color_t* c);

static color_t COLOR_RED = (color_t){255, 0, 0, 255};
static color_t COLOR_GREEN = (color_t){0, 255, 0, 255};
static color_t COLOR_BLUE = (color_t){0, 0, 255, 255};
static color_t COLOR_GRAY = (color_t){128, 128, 128, 255};