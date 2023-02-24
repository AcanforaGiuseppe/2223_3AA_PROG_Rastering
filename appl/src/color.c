#include "color.h"

color_t color_mult(color_t* color, float scalar) 
{
    color_t result;
    result.r = (int)((float)color->r * scalar);
    result.g = (int)((float)color->g * scalar);
    result.b = (int)((float)color->b * scalar);
    result.a = (int)((float)color->a * scalar);
    return result;
}

color_t color_add(color_t* c1, color_t* c2) 
{
    color_t result;
    result.r = c1->r + c2->r;
    result.g = c1->g + c2->g;
    result.b = c1->b + c2->b;
    result.a = c1->a + c2->a;
    return result;
}