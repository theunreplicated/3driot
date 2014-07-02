#ifndef IMPORT_OBJECT_STRUCT_H
#define IMPORT_OBJECT_STRUCT_H
#include "dingens_struct_base.h"
#include <array>
#include <vector>
struct Mesh_RenderObject :RenderStructBase{
	PrimitiveType draw_primitive;
	int num_tex_coords;
	float * vertices/*durch 3 für einzelne Vertices*/; unsigned int size_vertices/*totale länge,muss noch durch 3 geteilt werden*/;
	unsigned int num_indices = 0; unsigned int * indices/*@TODO:unsigned int oder long ist wohl besser*/;
	const char * mesh_name, *node_name;

	std::vector<std::array<std::array<float, 4>, 4>>transform_matrices;//@TODO:Matrices(Matrizen) wieder auf den Heap
};
#endif