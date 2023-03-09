#include "aiv-math.h"

int min3(int v1, int v2, int v3) 
{
    int result = v1;

    if (v2 < result)
    result = v2;

    if (v3 < result)
    result = v3;

    return result;
}

int max3(int v1, int v2, int v3) 
{
    int result = v1;

    if (v2 > result)
    result = v2;

    if (v3 > result) 
    result = v3;

    return result;
}

int det(vector2_t p, vector2_t v1, vector2_t v2) 
{   
    // A->
    int vx = v2.x - v1.x;
    int vy = v2.y - v1.y;

    // B->
    int px = p.x - v1.x;
    int py = p.y - v1.y;

    return vx * py - vy * px;
}

float clampf(float v, float min, float max) 
{
    if (v < min)
    return min;

    if (v > max)
    return max;
    
    return v;
}