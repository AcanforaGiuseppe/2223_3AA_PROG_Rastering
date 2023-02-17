#pragma once
#include "screen.h"
#include "aiv-texture.h"

typedef enum {
    VGPU_FLAG_NONE    = 0,
    VGPU_FLAG_TEXTURE = 1 << 0,
    VGPU_FLAG_COLOR   = 1 << 1,
} vgpu_flags_e;

typedef struct {
    screen_t* screen;
    texture_t* texture;
    int flags;
} vgpu_t;