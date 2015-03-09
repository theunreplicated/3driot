#ifndef INC_GL_STRUCT_H
#define INC_GL_STRUCT_H
#include <array>
#include <vector>
#include "OpenGL_Data_Types.h"
#include "WindowStructs.h"
#include <glm/mat4x4.hpp>

#include "dingens_struct_base.h"






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
	//unsigned int /*vertices_num,*/ indices_num/*könnte man eigentlich streichen*/;
	int draw_call_num_elements;
	size_t vertices_totalsize, indices_totalsize,texcoords_totalsize;
	glm::mat4 matrix; 
	bool enable_matrix = false;
};

//@TODO:mergen mit dem von windowstructs
/*struct GLRect{
	//	WindowRect() :width(0){};//struct ohne KonstruktOOOOR leider nur begrenzt einsetzbar,aber mit {} init werden alle anderen Values auf default-null gesetzt
	int width, height, x, y;

};*/

//typedef Windows::WindowRect GLRect;
#endif