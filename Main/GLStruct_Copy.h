#ifndef INC_GL_STRUCT_COPY_H
#define INC_GL_STRUCT_COPY_H
#include <glm/mat4x4.hpp>
//#include "../window2/ImageLoader.h"
struct Interals_do_not_touch{
	unsigned int vertex_buffer, indices_buffer, texcoords_buffer, Diffuse_Texture_IDs;

}; enum PrimitiveType{ PR_TRIANGLE = 0x0004/*=GL_TRIANGLES*/ };
struct image_stor{
	int width, height;
	unsigned char /** texture_bytes,*/*bits;
	int format; unsigned int il_image_id;
};
struct RenderStructBase{
	float * tex_coords; bool has_tex_coord = false;
	image_stor texture_data; bool has_texture = false;
};
enum draw_method{ kArrays, kElements, kInvisible };//konstant davor,falls Konflikte
struct THREEDObject :RenderStructBase, Interals_do_not_touch{
	PrimitiveType draw_primitive = PR_TRIANGLE;
	draw_method dm;
	/*GL*/float * vertices;
	bool has_indices /*= true*/;//@TODO:was damit machen
	/*GLu*/unsigned int * indices = 0;//nur falls Elemente
	int vertices_num, indices_num/*könnte man eigentlich streichen*/;
	int draw_call_num_elements;
	size_t vertices_totalsize, indices_totalsize, texcoords_totalsize;
	glm::mat4 matrix;
	bool enable_matrix = false;
};
#endif