#define CLOVE_SUITE_NAME ObjParserTest
#include "clove-unit.h"
#include "test-utils.h"
#include "obj-parser.h"

CLOVE_TEST(TestCountObjMeshData) {
   const char* base_test_path = CLOVE_EXEC_BASE_PATH();
   const char* source_path = tut_concat_path(base_test_path, "\\resources\\quad.obj");

   obj_t* mesh = obj_parser_parse(source_path);

   CLOVE_NOT_NULL(mesh);
   CLOVE_INT_EQ(4, mesh->vertex_count);
   CLOVE_INT_EQ(4, mesh->vertex_texture_count);
   CLOVE_INT_EQ(1, mesh->vertex_normal_count);
   CLOVE_INT_EQ(2, mesh->face_count);
}

CLOVE_TEST(TestQuadParse) {
   const char* base_test_path = CLOVE_EXEC_BASE_PATH();
   const char* source_path = tut_concat_path(base_test_path, "\\resources\\quad.obj");

   obj_t* mesh = obj_parser_parse(source_path);

   //T1 - V1
   CLOVE_FLOAT_EQ(mesh->triangles[0].v1.position.x, 1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v1.position.y, -1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v1.position.z, 0.f);

   CLOVE_FLOAT_EQ(mesh->triangles[0].v1.uv.x, 1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v1.uv.y, 0.f);

   CLOVE_FLOAT_EQ(mesh->triangles[0].v1.normal.x, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v1.normal.y, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v1.normal.z, 1.f);

   //T1 - V2
   CLOVE_FLOAT_EQ(mesh->triangles[0].v2.position.x, -1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v2.position.y, -1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v2.position.z, 0.f);

   CLOVE_FLOAT_EQ(mesh->triangles[0].v2.uv.x, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v2.uv.y, 0.f);

   CLOVE_FLOAT_EQ(mesh->triangles[0].v2.normal.x, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v2.normal.y, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v2.normal.z, 1.f);

   //T1 - V3
   CLOVE_FLOAT_EQ(mesh->triangles[0].v3.position.x, -1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v3.position.y, 1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v3.position.z, 0.f);

   CLOVE_FLOAT_EQ(mesh->triangles[0].v3.uv.x, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v3.uv.y, 1.f);

   CLOVE_FLOAT_EQ(mesh->triangles[0].v3.normal.x, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v3.normal.y, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[0].v3.normal.z, 1.f);

   //T2 - V1
   CLOVE_FLOAT_EQ(mesh->triangles[1].v1.position.x, 1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v1.position.y, 1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v1.position.z, 0.f);

   CLOVE_FLOAT_EQ(mesh->triangles[1].v1.uv.x, 1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v1.uv.y, 1.f);

   CLOVE_FLOAT_EQ(mesh->triangles[1].v1.normal.x, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v1.normal.y, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v1.normal.z, 1.f);

   //T2 - V2
   CLOVE_FLOAT_EQ(mesh->triangles[1].v2.position.x, 1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v2.position.y, -1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v2.position.z, 0.f);

   CLOVE_FLOAT_EQ(mesh->triangles[1].v2.uv.x, 1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v2.uv.y, 0.f);

   CLOVE_FLOAT_EQ(mesh->triangles[1].v2.normal.x, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v2.normal.y, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v2.normal.z, 1.f);

   //T2 - V3
   CLOVE_FLOAT_EQ(mesh->triangles[1].v3.position.x, -1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v3.position.y, 1.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v3.position.z, 0.f);

   CLOVE_FLOAT_EQ(mesh->triangles[1].v3.uv.x, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v3.uv.y, 1.f);

   CLOVE_FLOAT_EQ(mesh->triangles[1].v3.normal.x, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v3.normal.y, 0.f);
   CLOVE_FLOAT_EQ(mesh->triangles[1].v3.normal.z, 1.f);
}
