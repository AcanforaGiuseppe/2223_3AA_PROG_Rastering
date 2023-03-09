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

color_t color_clamp(color_t* c)
{
    color_t result;
    result.r = c->r > 255 ? 255 : c->r;
    result.g = c->g > 255 ? 255 : c->g;
    result.b = c->b > 255 ? 255 : c->b;
    result.a = c->a > 255 ? 255 : c->a;

    return result;
}