#pragma once
#include "vector.h"
#include <stdlib.h>

typedef struct {
    vector3f_t position;
    float vertical_fov_degrees;
    int width;
    int height;
} camera_t;

camera_t* camera_new(float fov, int sw, int sh);

vector2_t camera_world_to_screen_space(camera_t* camera, vector3f_t wp);
vector3f_t camera_world_to_camera_space(camera_t* camera, vector3f_t* wp);