#ifndef INC_GL_STRUCT_H
#define INC_GL_STRUCT_H
#include <array>
#include <vector>
#include "OpenGL_Data_Types.h"
#include "WindowStructs.h"
//#include <glm/mat4x4.hpp>
#include "Assimp_Material_Importer.h"
enum PrimitiveType{ PR_TRIANGLE = 0x0004/*=GL_TRIANGLES*/ };
struct RenderStructBase{
	float * tex_coords; bool has_tex_coord = false;
	image_stor texture_data; bool has_texture = false;
};
struct Mesh_RenderObject:RenderStructBase{
	PrimitiveType draw_primitive;
	int num_tex_coords;
	float * vertices/*durch 3 für einzelne Vertices*/; unsigned int size_vertices/*totale länge,muss noch durch 3 geteilt werden*/;
	unsigned int num_indices = 0; unsigned int * indices/*@TODO:unsigned int oder long ist wohl besser*/;
	const char * mesh_name, *node_name;
	
	std::vector<std::array<std::array<float, 4>, 4>>transform_matrices;//@TODO:Matrices(Matrizen) wieder auf den Heap
};

struct Interals_do_not_touch{
GLuint 	vertex_buffer, indices_buffer, texcoords_buffer, Diffuse_Texture_IDs;

};
enum draw_method{ kArrays, kElements,kInvisible };//konstant davor,falls Konflikte
struct THREEDObject:RenderStructBase,Interals_do_not_touch{
	PrimitiveType draw_primitive=PR_TRIANGLE;
	draw_method dm;
	/*GL*/float * vertices;
	bool has_indices /*= true*/;//@TODO:was damit machen
	/*GLu*/unsigned int * indices = NULL;//nur falls Elemente
	int vertices_num, indices_num/*könnte man eigentlich streichen*/;
	int draw_call_num_elements;
	size_t vertices_totalsize, indices_totalsize,texcoords_totalsize;
	float* matrix;
	bool enable_matrix = false;
};

//@TODO:mergen mit dem von windowstructs
/*struct GLRect{
	//	WindowRect() :width(0){};//struct ohne KonstruktOOOOR leider nur begrenzt einsetzbar,aber mit {} init werden alle anderen Values auf default-null gesetzt
	int width, height, x, y;

};*/

typedef Windows::WindowRect GLRect;
#endif