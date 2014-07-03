#ifndef DINGENS_STRUCT_BASE_H
#define DINGENS_STRUCT_BASE_H
#ifndef HIDE_IMG_STRUCT_FROM_MAIN
#include "IMGSTRUCTS.h"
enum PrimitiveType{ PR_TRIANGLE = 0x0004/*=GL_TRIANGLES*/ };

struct RenderStructBase{
	float * tex_coords; bool has_tex_coord = true;
	image_stor texture_data; bool has_texture = true;//@TODO:ändern
};
#endif
#endif