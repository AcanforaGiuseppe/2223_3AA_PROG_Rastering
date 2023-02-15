#include "scene.h"
#include "SDL.h"
#include <stdlib.h>
#include "screen.h"
#include "line-raster.h"
#include "vector.h"
#include "triangle-raster.h"

scene_t* scene_create(int screen_width, int screen_height, SDL_Renderer* r) {
    scene_t* scene = (scene_t*)malloc(sizeof(scene_t));
    scene->screen = screen_new(screen_width, screen_height, r);
    scene->camera = camera_new(60, screen_width, screen_height);
    //scene->camera->position = (vector3f_t){-5, 0, 0};
    scene->quad = obj_parser_parse("bin\\appl\\resources\\quad.obj");
    scene->suzanne = obj_parser_parse("bin\\appl\\resources\\suzanne.obj");
    return scene;
}

void draw_quad(scene_t* s, float delta_time) {
    color_t green = {0, 255, 0, 255};

     for(int i=0; i < s->quad->face_count; ++i) {
        vector3f_t* wp1 = (vector3f_t*)&(s->quad->triangles[i].v1.position);
        vector3f_t* wp2 = (vector3f_t*)&(s->quad->triangles[i].v2.position);
        vector3f_t* wp3 = (vector3f_t*)&(s->quad->triangles[i].v3.position);

        wp1->z = -4;
        wp2->z = -4;
        wp3->z = -4;

        vector2_t p1 = camera_world_to_screen_space(s->camera, *wp1);
        vector2_t p2 = camera_world_to_screen_space(s->camera, *wp2);
        vector2_t p3 = camera_world_to_screen_space(s->camera, *wp3);
        bbox_triangle_raster(s->screen, p1, p2, p3, green);
    }
}


void draw_suzanne(scene_t* s, float delta_time, bool wire_frame) {
    color_t red = {255, 0, 0, 255};

    obj_t* obj = s->suzanne;

    static float rotation = 0.f;
    rotation +=  2.f * delta_time;

     for(int i=0; i < obj->face_count; ++i) {
        vector3f_t* lp1 = (vector3f_t*)&(obj->triangles[i].v1.position);
        vector3f_t* lp2 = (vector3f_t*)&(obj->triangles[i].v2.position);
        vector3f_t* lp3 = (vector3f_t*)&(obj->triangles[i].v3.position);

        //scale - rotate - traslate
        vector3f_t wp1 = vector3f_mult(lp1, 2);
        vector3f_t wp2 = vector3f_mult(lp2, 2);
        vector3f_t wp3 = vector3f_mult(lp3, 2);

        wp1 = vector3f_rotate_y(&wp1, rotation);
        wp2 = vector3f_rotate_y(&wp2, rotation);
        wp3 = vector3f_rotate_y(&wp3, rotation);

        vector3f_t transl = (vector3f_t){0, 0, 5.f};
        wp1 = vector3f_sub(&wp1, &transl);
        wp2 = vector3f_sub(&wp2, &transl);
        wp3 = vector3f_sub(&wp3, &transl);
        
        vector2_t p1 = camera_world_to_screen_space(s->camera, wp1);
        vector2_t p2 = camera_world_to_screen_space(s->camera, wp2);
        vector2_t p3 = camera_world_to_screen_space(s->camera, wp3);

        if (wire_frame) {
            dda_line_raster(s->screen, p1.x, p1.y, p2.x, p2.y, red); 
            dda_line_raster(s->screen, p1.x, p1.y, p3.x, p3.y, red); 
            dda_line_raster(s->screen, p2.x, p2.y, p3.x, p3.y, red); 
        } else {
            bbox_triangle_raster(s->screen, p1, p2, p3, red);
        }
    }
}

void scene_update(scene_t* s, float delta_time) {
    screen_clear(s->screen);
   
    color_t red = {255, 0, 0, 255};

    static float x1 = 50;
    static float y1 = 50;
    static float x2 = 200;
    static float y2 = 250;

    //dda_line_raster(s->screen, (int)x1, (int)y1, (int)x2, (int)y2, red);
    //dda_line_raster(s->screen, x1+10, y1, x2+10, y2, red);
    float speed = 1;
    x1 += speed * delta_time;
    x2 += speed * delta_time;


    //Draw Triangle Edges
    /*
    dda_line_raster(s->screen, 320, 240, 240, 460, red);  //left
    dda_line_raster(s->screen, 320, 240, 400, 460, red); //right
    dda_line_raster(s->screen, 240, 460, 400, 460, red); //base
    */

    /*
    vector2_t p1 = { 320, 240 };
    vector2_t p2 = { 240, 460 };
    vector2_t p3 = { 400, 460 };
    */
    vector3f_t wp1 = { 0.f, 0.f,   -10 };
    vector3f_t wp2 = { -4.f, -4.f, -10 };
    vector3f_t wp3 = { 4.f, -4.f,  -10 };

    color_t green = {0, 255, 0, 255};


    vector2_t p1 = camera_world_to_screen_space(s->camera, wp1);
    vector2_t p2 = camera_world_to_screen_space(s->camera, wp2);
    vector2_t p3 = camera_world_to_screen_space(s->camera, wp3);
    //bbox_triangle_raster(s->screen, p1, p2, p3, green);

    //draw_quad(s, delta_time);

    draw_suzanne(s, delta_time, true);
   
    screen_blit(s->screen);
}

void scene_destroy(scene_t* s) {
    screen_free(s->screen);
    obj_parser_free(s->quad);
    obj_parser_free(s->suzanne);
    free(s);
}