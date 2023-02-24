#include "vector.h"
#include <math.h>
#include "aiv-math.h"

vector3f_t vector3f_sub(vector3f_t* v1, vector3f_t* v2) 
{
    vector3f_t r;
    r.x = v1->x - v2->x;
    r.y = v1->y - v2->y;
    r.z = v1->z - v2->z;
    return r;
}

vector3f_t vector3f_rotate_y(vector3f_t* v, float degrees)
{
    float rads = degrees * M_PI / 180.f;

    vector3f_t result;
    result.x = cosf(rads) * v->x - sinf(rads) * v->z;
    result.y = v->y;
    result.z = sinf(rads) * v->x + cosf(rads) * v->z;
    return result;
}

vector3f_t vector3f_mult(vector3f_t* v, float scalar) 
{
    vector3f_t result;
    result.x = v->x * scalar;
    result.y = v->y * scalar;
    result.z = v->z * scalar;
    return result;
}

vector3f_t vector3f_norm(vector3f_t* v) 
{
    float inv_m = 1.f / vector3f_magn(v);
    return vector3f_mult(v, inv_m);
}

float vector3f_magn(vector3f_t* v)
{
    return sqrtf(vector3f_dot(v, v));
}

float vector3f_dot(vector3f_t* v1, vector3f_t* v2)
{
    return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}