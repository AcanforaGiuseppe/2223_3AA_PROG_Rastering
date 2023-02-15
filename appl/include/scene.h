#ifndef SCENE_H
#define SCENE_H
#include "SDL.h"
#include "screen.h"
#include "camera.h"
#include "obj-parser.h"

typedef struct {
    screen_t* screen;
    camera_t* camera;
    obj_t* quad;
    obj_t* suzanne;
} scene_t;

scene_t* scene_create(int w, int h, SDL_Renderer*);
void scene_update(scene_t*, float delta_time);
void scene_destroy(scene_t*);

#endif //SCENE_H