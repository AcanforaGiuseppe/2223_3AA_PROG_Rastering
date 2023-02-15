#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
    float z;
} obj_parser_float3_t;

typedef struct {
    float x;
    float y;
} obj_parser_float2_t;

typedef struct {
    obj_parser_float3_t position;
    obj_parser_float2_t uv;
    obj_parser_float3_t normal;
} obj_vertex_t;

typedef struct {
    obj_vertex_t v1;
    obj_vertex_t v2;
    obj_vertex_t v3;
} obj_triangle_t;

typedef struct {
    size_t vertex_count;
    size_t vertex_texture_count;
    size_t vertex_normal_count;
    size_t face_count;
    obj_triangle_t* triangles;
} obj_t;

obj_t* obj_parser_parse(const char* path);
void obj_parser_free(obj_t* path);

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
    rewind(f);

    size_t v_index = 0;
    obj_parser_float3_t* vertexes = (obj_parser_float3_t*)malloc(sizeof(obj_parser_float3_t) * mesh->vertex_count);
    size_t vt_index = 0;
    obj_parser_float2_t* vertexes_texture = (obj_parser_float2_t*)malloc(sizeof(obj_parser_float2_t) * mesh->vertex_texture_count);
    size_t vn_index = 0;
    obj_parser_float3_t* vertexes_normal = (obj_parser_float3_t*)malloc(sizeof(obj_parser_float3_t) * mesh->vertex_normal_count);
    size_t f_index = 0;
    int* faces = (int*)malloc(sizeof(int) * 9 * mesh->face_count);

    while(fgets(buffer, buffer_size, f)) {
        char* context;
        char* token = strtok_s(buffer, " ", &context);
        if (strcmp(token, "v") == 0) {
            //x
            token = strtok_s(NULL, " ", &context);
            vertexes[v_index].x = atof(token);
            //y
            token = strtok_s(NULL, " ", &context);
            vertexes[v_index].y = atof(token);
            //z
            token = strtok_s(NULL, " ", &context);
            vertexes[v_index].z = atof(token);
            v_index++;
        }
        else if (strcmp(token, "vt") == 0) {
            //x
            token = strtok_s(NULL, " ", &context);
            vertexes_texture[vt_index].x = atof(token);
            //y
            token = strtok_s(NULL, " ", &context);
            vertexes_texture[vt_index].y = atof(token);
            vt_index++;
        }
        else if (strcmp(token, "vn") == 0) {
            //x
            token = strtok_s(NULL, " ", &context);
            vertexes_normal[vn_index].x = atof(token);
            //y
            token = strtok_s(NULL, " ", &context);
            vertexes_normal[vn_index].y = atof(token);
            //z
            token = strtok_s(NULL, " ", &context);
            vertexes_normal[vn_index].z = atof(token);
            vn_index++;
        }
        else if (strcmp(token, "f") == 0) {
            for (size_t i = 0; i < 3; i++)
            {
                int index = f_index * 9 + i * 3;
                //v
                token = strtok_s(NULL, "/", &context);
                faces[index + 0] = atoi(token) - 1;
                //vt
                token = strtok_s(NULL, "/", &context);
                faces[index + 1] = atoi(token) - 1;
                //vn
                token = strtok_s(NULL, " ", &context);
                faces[index + 2] = atoi(token) - 1;
            }
            f_index++;
        }
    }
    fclose(f);

    mesh->triangles = (obj_triangle_t*)malloc(sizeof(obj_triangle_t) * mesh->face_count);
    for (size_t i = 0; i < mesh->face_count; i++)
    {
        int index = i * 9;
        //V1
        //position
        int vertex_index = faces[index];
        mesh->triangles[i].v1.position = vertexes[vertex_index];
        //uv
        int vertex_texture_index = faces[index + 1];
        mesh->triangles[i].v1.uv = vertexes_texture[vertex_texture_index];
        //normal
        int vertex_normal_index = faces[index + 2];
        mesh->triangles[i].v1.normal = vertexes_normal[vertex_normal_index];

        //V2
        //position
        vertex_index = faces[index + 3];
        mesh->triangles[i].v2.position = vertexes[vertex_index];
        //uv
        vertex_texture_index = faces[index + 4];
        mesh->triangles[i].v2.uv = vertexes_texture[vertex_texture_index];
        //normal
        vertex_normal_index = faces[index + 5];
        mesh->triangles[i].v2.normal = vertexes_normal[vertex_normal_index];

        //V3
        //position
        vertex_index = faces[index + 6];
        mesh->triangles[i].v3.position =  vertexes[vertex_index];
        //uv
        vertex_texture_index = faces[index + 7];
        mesh->triangles[i].v3.uv = vertexes_texture[vertex_texture_index];
        //normal
        vertex_normal_index = faces[index + 8];
        mesh->triangles[i].v3.normal = vertexes_normal[vertex_normal_index];
    }
    
    free(vertexes);
    free(vertexes_normal);
    free(vertexes_texture);
    free(faces);

    return mesh;
}

void obj_parser_free(obj_t* obj) 
{
    free(obj->triangles);
    free(obj);
}

#endif