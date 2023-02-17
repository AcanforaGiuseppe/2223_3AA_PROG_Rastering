#include "line-raster.h"

void dda_line_raster(screen_t* screen, int x1, int y1, int x2, int y2, color_t color) 
{
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);
    int steps = (dx > dy) ? dx : dy;

    int sx = (x1 > x2) ? -1 : 1;
    int sy = (y1 > y2) ? -1 : 1;

    float step_x = (float)dx * (float)sx / (float)steps;
    float step_y = (float)dy * (float)sy / (float)steps;

    float x = x1;
    float y = y1;
    
    for(int i=0; i <= steps; ++i) 
    {
        screen_put_pixel(screen, x, y, 0.f, color);
        x += step_x;
        y += step_y;
    }
}