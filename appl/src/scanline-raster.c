#include "scanline-raster.h"

void _sort_by_y(vector2_t** p1, vector2_t** p2, vector2_t** p3) 
{   
    vector2_t* temp;
    if ((*p1)->y > (*p2)->y ) { 
        temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }

    if ((*p2)->y > (*p3)->y ) { 
        temp = *p2;
        *p2 = *p3;
        *p3 = temp;
    }

    if ((*p1)->y > (*p2)->y ) { 
        temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }
}

float _interpolate_scalar(float v1, float v2, float gradient) 
{
    return v1 + gradient * (v2 - v1);
}

void _interpolate_row(screen_t* screen, int y, vector2_t* left_edge_v1, vector2_t* left_edge_v2, vector2_t* right_edge_v1, vector2_t* right_edge_v2)
{
    float left_gradient_y = 1.f;
    if (left_edge_v1->y != left_edge_v2->y) 
    {
        left_gradient_y = (float)(y - left_edge_v1->y) / (float)(left_edge_v2->y - left_edge_v1->y);
    }

    float right_gradient_y = 1.f;
    if (right_edge_v1->y != right_edge_v2->y) 
    {
        right_gradient_y = (float)(y - right_edge_v1->y) / (float)(right_edge_v2->y - right_edge_v1->y);
    }

    int left_x = (int)_interpolate_scalar((float) left_edge_v1->x, (float) left_edge_v2->x, left_gradient_y);
    int right_x = (int)_interpolate_scalar((float) right_edge_v1->x, (float) right_edge_v2->x, right_gradient_y);

    for(int x = left_x; x <= right_x; ++x) 
    {
        color_t red = (color_t){255, 0, 0, 255};
        screen_put_pixel(screen, x, y, red);
    }
}

void scanline_raster(screen_t* screen, vector2_t* p1, vector2_t* p2, vector2_t* p3) 
{
    _sort_by_y(&p1, &p2, &p3);

    float inv_slope_p1p2 = (float)(p2->x - p1->x) / (float)(p2->y - p1->y);
    float inv_slope_p1p3 = (float)(p3->x - p1->x) / (float)(p3->y - p1->y);

    // <|
    if (inv_slope_p1p2 < inv_slope_p1p3) 
    {
        for(int y = p1->y; y <= p3->y; ++y) 
        {
            if (y < p2->y) //phase1: upper triangle: left: p1p2 right p1p3
            { 
                _interpolate_row(screen, y, p1,p2, p1,p3);
            } 
            else //phase2: lower triangle: left: p2p3 right p1p3
            { 
                _interpolate_row(screen, y, p2,p3, p1,p3);
            }
        }
    } 
    else // |>
    {
         for(int y = p1->y; y <= p3->y; ++y) 
        {
            if (y < p2->y) //phase1: upper triangle: left: p1p3 right p1p2
            { 
                _interpolate_row(screen, y, p1,p3, p1,p2);
            } 
            else //phase2: lower triangle: left: p1p3 right p2p3
            { 
                _interpolate_row(screen, y, p1,p3, p2,p3);
            }
        }
    }
}