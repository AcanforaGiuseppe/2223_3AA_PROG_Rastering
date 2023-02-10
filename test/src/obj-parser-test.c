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
