#include "scanline-raster.h"
#include <stdio.h>
#include "aiv-math.h"

void _sort_by_y(vertex_t** v1, vertex_t** v2, vertex_t** v3) 
{   
    vertex_t* temp;
    if ((*v1)->screen_pos->y > (*v2)->screen_pos->y )
    { 
        temp = *v1;
        *v1 = *v2;
        *v2 = temp;
    }

    if ((*v2)->screen_pos->y > (*v3)->screen_pos->y )
    { 
        temp = *v2;
        *v2 = *v3;
        *v3 = temp;
    }

    if ((*v1)->screen_pos->y > (*v2)->screen_pos->y )
    { 
        temp = *v1;
        *v1 = *v2;
        *v2 = temp;
    }
}

float _interpolate_scalar(float v1, float v2, float gradient) 
{
    return v1 + gradient * (v2 - v1);
}

color_t _interpolate_color(color_t* c1, color_t* c2, float gradient) 
{
    color_t result;
    result.r = (Uint8)_interpolate_scalar((float)c1->r, (float)c2->r, gradient);
    result.g = (Uint8)_interpolate_scalar((float)c1->g, (float)c2->g, gradient);
    result.b = (Uint8)_interpolate_scalar((float)c1->b, (float)c2->b, gradient);
    result.a = (Uint8)_interpolate_scalar((float)c1->a, (float)c2->a, gradient);

    return result;
}

vector2f_t _interpolate_vector2f(vector2f_t* v1, vector2f_t* v2, float gradient) 
{
    vector2f_t result;
    result.x = _interpolate_scalar(v1->x, v2->x, gradient);
    result.y = _interpolate_scalar(v1->y, v2->y, gradient);
    
    return result;
}

vector3f_t _interpolate_vector3f(vector3f_t* v1, vector3f_t* v2, float gradient) 
{
    vector3f_t result;
    result.x = _interpolate_scalar(v1->x, v2->x, gradient);
    result.y = _interpolate_scalar(v1->y, v2->y, gradient);
    result.z = _interpolate_scalar(v1->z, v2->z, gradient);

    return result;
}


void _interpolate_row(vgpu_t* gpu, int y, vertex_t* left_edge_v1, vertex_t* left_edge_v2, vertex_t* right_edge_v1, vertex_t* right_edge_v2)
{
    float left_gradient_y = 1.f;

    if (left_edge_v1->screen_pos->y != left_edge_v2->screen_pos->y) 
        left_gradient_y = (float)(y - left_edge_v1->screen_pos->y) / (float)(left_edge_v2->screen_pos->y - left_edge_v1->screen_pos->y);

    float right_gradient_y = 1.f;

    if (right_edge_v1->screen_pos->y != right_edge_v2->screen_pos->y) 
        right_gradient_y = (float)(y - right_edge_v1->screen_pos->y) / (float)(right_edge_v2->screen_pos->y - right_edge_v1->screen_pos->y);

    int left_x = (int)_interpolate_scalar((float) left_edge_v1->screen_pos->x, (float) left_edge_v2->screen_pos->x, left_gradient_y);
    int right_x = (int)_interpolate_scalar((float) right_edge_v1->screen_pos->x, (float) right_edge_v2->screen_pos->x, right_gradient_y);

    float left_z = _interpolate_scalar((float) left_edge_v1->z_pos, (float) left_edge_v2->z_pos, left_gradient_y);
    float right_z = _interpolate_scalar((float) right_edge_v1->z_pos, (float) right_edge_v2->z_pos, right_gradient_y);

    color_t left_color;
    color_t right_color;

    if (gpu->flags & VGPU_FLAG_COLOR) 
    {
        left_color = _interpolate_color(left_edge_v1->color, left_edge_v2->color, left_gradient_y);
        right_color = _interpolate_color(right_edge_v1->color, right_edge_v2->color, right_gradient_y);
    }
    
    vector2f_t left_uv;
    vector2f_t right_uv;

    if (gpu->flags & VGPU_FLAG_TEXTURE) 
    {
        left_uv = _interpolate_vector2f(left_edge_v1->text_coord, left_edge_v2->text_coord, left_gradient_y);
        right_uv = _interpolate_vector2f(right_edge_v1->text_coord, right_edge_v2->text_coord, right_gradient_y); 
    }

    vector3f_t left_world_norm = _interpolate_vector3f(left_edge_v1->world_norm, left_edge_v2->world_norm, left_gradient_y);
    vector3f_t right_world_norm = _interpolate_vector3f(right_edge_v1->world_norm, right_edge_v2->world_norm, right_gradient_y);

    vector3f_t left_world_pos = _interpolate_vector3f(left_edge_v1->world_pos, left_edge_v2->world_pos, left_gradient_y);
    vector3f_t right_world_pos = _interpolate_vector3f(right_edge_v1->world_pos, right_edge_v2->world_pos, right_gradient_y);

    for(int x = left_x; x <= right_x; ++x) 
    {
        float gradient_x = 1.f;

        if (left_x < right_x) 
            gradient_x = (float)(x - left_x) / (float)(right_x - left_x);

        float sampled_z = _interpolate_scalar(left_z, right_z, gradient_x);

        color_t sampled_color;

        if (gpu->flags & VGPU_FLAG_COLOR) 
            sampled_color = _interpolate_color(&left_color, &right_color, gradient_x);
        
        if (gpu->flags & VGPU_FLAG_TEXTURE) 
        {
            vector2f_t uv = _interpolate_vector2f(&left_uv, &right_uv, gradient_x);
            texture_t* text = gpu->texture;

            int text_x = (int)( (float)text->width * uv.x ) % text->width; // protect and take account for uv rolling 
            int text_y = (int)( (float)text->height * (1.f - uv.y)) % text->height; // protect and take account for uv rolling

            int text_index = (text_y * text->width + text_x) * text->pixel_size;
            sampled_color.r = text->data[text_index + 0];
            sampled_color.g = text->data[text_index + 1];
            sampled_color.b = text->data[text_index + 2];
            sampled_color.a = text->data[text_index + 3];
        }

        // Compute Phong
        // 1. Ambient
        float ambiente_intensity = 0.1f;
        color_t ambient = color_mult(&sampled_color, ambiente_intensity);

        // 2. Diffuse
        vector3f_t world_pos = _interpolate_vector3f(&left_world_pos, &right_world_pos, gradient_x);
        vector3f_t dir_to_light = vector3f_sub(gpu->point_light_pos, &world_pos);
        dir_to_light = vector3f_norm(&dir_to_light);

        vector3f_t world_norm = _interpolate_vector3f(&left_world_norm, &right_world_norm, gradient_x);
        world_norm = vector3f_norm(&world_norm);

        float cosLN = vector3f_dot(&dir_to_light, &world_norm);
        float lambert = clampf(cosLN, 0.f, 1.f);
        color_t diffuse = color_mult(&sampled_color, lambert);

        // 3. Specular
        vector3f_t dir_to_eye = vector3f_sub(gpu->camera_pos, &world_pos);
        dir_to_eye = vector3f_norm(&dir_to_eye);

        vector3f_t dir_light_to_point = vector3f_mult(&dir_to_light, -1.f);
        vector3f_t dir_to_light_refl = vector3f_refl(&dir_light_to_point, &world_norm); //already normalized becouse of dir_to_light

        float cosER = vector3f_dot(&dir_to_eye, &dir_to_light_refl);
        float specular_value = clampf(cosER, 0.f, 1.f);
        color_t specular_color = (color_t){255, 255, 255, 255};
        color_t specular = color_mult(&specular_color, powf(specular_value, 50.f));

        color_t phong = (color_t){0, 0, 0, 0};
        phong = color_add(&phong, &ambient);
        phong = color_add(&phong, &diffuse);
        phong = color_add(&phong, &specular);
        phong = color_clamp(&phong);

        screen_put_pixel(gpu->screen, x, y, sampled_z, phong);
    }
}

void scanline_raster(vgpu_t* gpu, vertex_t* v1, vertex_t* v2, vertex_t* v3)
{
    _sort_by_y(&v1, &v2, &v3);

    vector2_t* p1 = v1->screen_pos;
    vector2_t* p2 = v2->screen_pos;
    vector2_t* p3 = v3->screen_pos;
    
    float inv_slope_p1p2 = (float)(p2->x - p1->x) / (float)(p2->y - p1->y);
    float inv_slope_p1p3 = (float)(p3->x - p1->x) / (float)(p3->y - p1->y);

    // <|
    if (inv_slope_p1p2 < inv_slope_p1p3) 
    {
        for(int y = p1->y; y <= p3->y; ++y) 
        {
            if (y < p2->y) // phase1: upper triangle: left: p1p2 right p1p3
                _interpolate_row(gpu, y, v1,v2, v1,v3);
            else // phase2: lower triangle: left: p2p3 right p1p3
                _interpolate_row(gpu, y, v2,v3, v1,v3);
        }
    } 
    else // |>
    {
         for(int y = p1->y; y <= p3->y; ++y) 
        {
            if (y < p2->y) //phase1: upper triangle: left: p1p3 right p1p2
                _interpolate_row(gpu, y, v1,v3, v1,v2);
            else //phase2: lower triangle: left: p1p3 right p2p3
                _interpolate_row(gpu, y, v1,v3, v2,v3);
        }
    }
}