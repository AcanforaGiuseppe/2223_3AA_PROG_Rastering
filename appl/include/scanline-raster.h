#pragma once

#include "screen.h"
#include "vector.h"
#include "color.h"

typedef struct {
    vector2_t* screen_pos;
    color_t*  color;
    float z_pos;
} vertex_t;


void scanline_raster(screen_t* screen, vertex_t* v1, vertex_t* v2, vertex_t* v3);