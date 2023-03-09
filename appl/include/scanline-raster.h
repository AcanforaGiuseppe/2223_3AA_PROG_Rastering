#pragma once

#include "screen.h"
#include "vector.h"
#include "color.h"
#include "vgpu.h"

typedef struct
{
    vector2_t* screen_pos;
    color_t*  color;
    float z_pos;
    vector2f_t* text_coord;
    vector3f_t* world_norm;
    vector3f_t* world_pos;
} vertex_t;


void scanline_raster(vgpu_t* gpu, vertex_t* v1, vertex_t* v2, vertex_t* v3);