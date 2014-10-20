#ifndef GL_MAIN_H
#define GL_MAIN_H
#include "OpenGL_Data_Types.h"
#include <iostream>
#include <string>
#include <fstream>
//#include "OpenGL_Utils.h"
//#include "GLStructs.h"
//#include "Matrix.h"
#include "WindowStructs.h"
#include "Import_Object_Struct.h"
#include <glm\mat4x4.hpp>
#include "GLProgram.h"
#include "ShaderSource.h"
//mat#include <glm/mat4x4.hpp>
using std::vector;
typedef Windows::WindowRect GLRect;
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
class GLMain{

public:

	GLMain(/*void(*swapBuffersFunc)(),*/T_swapBuffersFuncType swapBuffersFunc2, T_swapBuffers_class_reference *swapBuffersFuncClass,bool use_legacy_system_opengl);
	void render(bool swap_the_Buffers=true);
	//void setNumDrawElements(int count);
	void addMesh_RenderObject_struct(Mesh_RenderObject *obj, float* pass_matrix=0);
	void initGL(GL_Program*program_to_start_with);
	void setViewPort(GLRect rect);
	std::vector<T_DRAW_STRUCTURE> draw_elements;
	//THREEDObject * draw_elements; 
	//Matrix m;
	//int num_draw_elements = 0;
	void add_to_buffer_and_add_to_draw_list(Mesh_RenderObject *obj, float* pass_matrix=0);
	void setCameraMatrix(glm::mat4 matrix);
	void setCameraTransformMatrix(glm::mat4 matrix);
	void setProjectionMatrix(glm::mat4 matrix);
	void set_framebuffer_to_position(bool to_offscreen_position=true);
	template <typename T_Gl_typ>
	T_Gl_typ * get_pixels_at_position(int pos_x, int pos_y, GLenum format,GLenum type, int width = 1, int height = 1);/*@TODO:template für typ*/
	void TEST_create_dummy_texture();
	void TEST_restore_dummy_texture();
	void set_current_program(GL_Program*program);
private:
	//T_swapBuffersFuncType swapBuffers;
	GL_Program*m_current_program;
	void swapBuffers();
	std::vector<T_DRAW_STRUCTURE> TEST_orig_draw_elements_for_restoring;

	GLsizei width, height;
	//GLuint * vertex_buffer,*indices_buffer,*texcoords_buffer;
	//GLuint * Diffuse_Texture_IDs;
	//std::vector<GLuint> vertex_buffer, indices_buffer, texcoords_buffer, Diffuse_Texture_IDs;
	void create_and_bind_framebuffer();
	void create_color_renderbuffer();
	void create_depth_renderbuffer();
	GLuint bindAttribLocation(const char* attrib_name);
	T_swapBuffers_class_reference *swap_buffers_func_class;
	T_swapBuffersFuncType swapBuffersFunc;
	//template <typename T_vertices_data, typename T_indices_data>
	//void addRenderElement(T_vertices_data &vertices, T_indices_data &indices, draw_method dm, int num_elements_to_draw);
	GLuint loc_Matrix;
	GLuint loc_Position, ID_framebuffer, colorRenderbuffer, depthRenderbuffer;
	GLuint texcoord_position,diffuse_Texture_sample_Loc;
	void fillBuffer(T_DRAW_STRUCTURE& pc);
	GLuint loadTexture(T_DRAW_STRUCTURE*mesh_data);
	glm::mat4 /*proj_camera_matrix,*/ camera_transform_matrix, camera_matrix, projection_matrix;
	bool m_use_legacy_system_opengl;
	bool use_vp_matrix;
	char * getErrorType(const GLenum errorno);

};



//using namespace OGL;
/*Test functions-müssen entfernt werden-have tov be removed

*/
//GLuint CreateSimpleTexture2D()
//{
	// Texture object handle
	//GLuint textureId;
	//https://code.google.com/p/opengles-book-samples/source/browse/trunk/Windows/Chapter_9/Simple_Texture2D/Simple_Texture2D.c
	// 2x2 Image, 3 bytes per pixel (R, G, B)
	/*GLubyte pixels[4 * 3] =
	{
		255, 0, 0, // Red
		0, 255, 0, // Green
		0, 0, 255, // Blue
		255, 255, 0  // Yellow
	};
	*/
	// Use tightly packed data
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate a texture object
	//glGenTextures(1, &textureId);

	// Bind the texture object
	//glBindTexture(GL_TEXTURE_2D, textureId);

	// Load the texture
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);


	// Set the filtering mode
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//	return textureId;

//}



/*template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
template <typename T_vertices_data, typename T_indices_data>//@NOTE:Hier ist die Reiheinfolge der template- (Davorschreibungen?)-wichtig,sonst meckert er,dass Deklaration und Def ungleich wären,lustigerweise sond sie doch gleich(nach der Anzeige),wtf
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::addRenderElement(T_vertices_data &vertices, T_indices_data &indices, draw_method dm, int num_elements_to_draw){
	T_DRAW_STRUCTURE pp;
	pp.dm = dm;
	/*const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};*/
//	pp.vertices_num = sizeof(vertices) / sizeof(GLfloat);
	/*pp.vertices_totalsize = sizeof(vertices);
	
	pp.vertices = new /*GL*//*float[sizeof(vertices)/sizeof(float)/*vertices müssen glfloat sein*//*];//@TODO. das hir irgendwie besser machen

	memcpy(pp.vertices, vertices, sizeof(vertices));
	if (indices != NULL){
		pp.indices_totalsize = sizeof(indices);
		pp.indices_num = sizeof(indices) / sizeof(unsigned int);
		//indices/kann auch null sein
		pp.indices = new /*GLu*//*unsigned int[pp.indices_num];
		memcpy(pp.indices, indices, sizeof(indices));
		
	}
	pp.draw_call_num_elements = num_elements_to_draw;
	//draw_elements[num_draw_elements] = pp;
	//num_draw_elements += 1;
	draw_elements.push_back(pp);

}*/

#include "GLMain.cpp"
#endif