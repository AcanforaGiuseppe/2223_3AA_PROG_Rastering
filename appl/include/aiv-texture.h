#pragma once
#include "SDL.h"

typedef struct
{
    Uint8* data;
    int width;
    int height;
    int pixel_size;
} texture_t;

texture_t* texture_load(const char* path);