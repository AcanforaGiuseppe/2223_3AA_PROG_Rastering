#pragma once

#include "vector.h"
#include "color.h"
#include "screen.h"
#include <stdbool.h>

void bbox_triangle_raster(screen_t* screen, vector2_t p1, vector2_t p2, vector2_t p3, color_t color);
bool bbox_is_point_in_triangle(vector2_t point, vector2_t p1, vector2_t p2, vector2_t p3);