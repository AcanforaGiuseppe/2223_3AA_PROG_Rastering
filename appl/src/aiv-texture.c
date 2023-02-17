#include "aiv-texture.h"
#include "SDL_image.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

texture_t* texture_load(const char* path) 
{
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL) {
        puts("FAILED TO LOAD IMAGE!!");
        return NULL;
    }

    texture_t* text = (texture_t*)malloc(sizeof(texture_t));   
    text->width = surface->w;
    text->height = surface->h;
    text->pixel_size = surface->format->BytesPerPixel;

    size_t size = text->width * text->height * text->pixel_size;
    text->data = (Uint8*)malloc(size);

    memcpy(text->data, surface->pixels, size);

    SDL_FreeSurface(surface);
    return text;
}

//TODO: implment free