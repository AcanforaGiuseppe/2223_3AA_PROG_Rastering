#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    size_t vertex_count;
    size_t vertex_texture_count;
    size_t vertex_normal_count;
    size_t face_count;
} obj_t;

obj_t* obj_parser_parse(const char* path);

#ifdef OBJ_PARSER_IMPLEMENTATION
obj_t* obj_parser_parse(const char* path) {
    FILE* f;
    errno_t result = fopen_s(&f, path, "r");
    if (result != 0) {
        printf("Unable to open file\n");
        return NULL;
    }

    obj_t* mesh = (obj_t*)malloc(sizeof(obj_t));
    if (!mesh) {
        printf("Unable to allocate memory\n");
        fclose(f);
        return NULL;
    }

    char buffer[1024];
    int buffer_size = 1024;
    mesh->vertex_count = 0;
    mesh->vertex_texture_count = 0;
    mesh->vertex_normal_count = 0;
    mesh->face_count = 0;

    while(fgets(buffer, buffer_size, f)) {
        if (strncmp(buffer, "v ", 2) == 0) {
            mesh->vertex_count++;
        }
        else if (strncmp(buffer, "vt ", 3) == 0) {
            mesh->vertex_texture_count++;
        }
        else if (strncmp(buffer, "vn ", 3) == 0) {
            mesh->vertex_normal_count++;
        }
        else if (strncmp(buffer, "f ", 2) == 0) {
            mesh->face_count++;
        }
    }

    fclose(f);
    return mesh;
}
#endif