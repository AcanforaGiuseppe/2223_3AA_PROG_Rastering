#pragma once
#include "screen.h"
#include "aiv-texture.h"

typedef enum
{
    VGPU_FLAG_NONE    = 0,
    VGPU_FLAG_TEXTURE = 1 << 0,
    VGPU_FLAG_COLOR   = 1 << 1,
} vgpu_flags_e;

typedef struct
{
    screen_t* screen;
    texture_t* texture;
    int flags;
    vector3f_t* point_light_pos;
    vector3f_t* camera_pos;
} vgpu_t;