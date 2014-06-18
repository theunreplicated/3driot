#ifndef INC_GL_STRUCT_H
#define INC_GL_STRUCT_H
#include <array>
enum PrimitiveType{ PR_TRIANGLE };
struct Mesh_RenderObject{
	PrimitiveType draw_primitive;
	float * vertices/*durch 3 für einzelne Vertices*/; unsigned int size_vertices/*totale länge,muss noch durch 3 geteilt werden*/;
	unsigned int num_indices = 0; unsigned int * indices/*@TODO:unsigned int oder long ist wohl besser*/;
	const char * mesh_name, *node_name;
	float * tex_coords; bool has_tex_coord = false;
	std::vector<std::array<std::array<float, 4>, 4>>transform_matrices;//@TODO:Matrices(Matrizen) wieder auf den Heap
};

enum draw_method{ kArrays, kElements };//konstant davor,falls Konflikte
struct THREEDObject{
	PrimitiveType draw_primitive;
	draw_method dm;
	/*GL*/float * vertices;
	/*GLu*/unsigned int * indices = NULL;//nur falls Elemente
	int vertices_num, indices_num/*könnte man eigentlich streichen*/;
	int draw_call_num_elements;
	size_t vertices_totalsize, indices_totalsize;
};

#endif