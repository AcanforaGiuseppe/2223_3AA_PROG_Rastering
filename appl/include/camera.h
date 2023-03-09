#pragma once
#include "vector.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    vector3f_t position;
    float vertical_fov_degrees;
    int width;
    int height;
} camera_t;

camera_t* camera_new(float fov, int sw, int sh);
vector2_t camera_world_to_screen_space(camera_t* camera, vector3f_t wp);
vector3f_t camera_world_to_camera_space(camera_t* camera, vector3f_t* wp);

bool triangle_is_facing_camera(vector3f_t* cp1, vector3f_t* cp2, vector3f_t* cp3);
bool triangle_is_within_camera(camera_t* camera, vector2_t* sp1, float cpz1, vector2_t* sp2, float cpz2, vector2_t* sp3, float cpz3);