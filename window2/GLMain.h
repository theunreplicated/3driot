#ifndef GL_MAIN_H
#define GL_MAIN_H
#include "OpenGLImport.h"
#include <iostream>
#include <string>
#include <fstream>
#include "OpenGL_Utils.h"
#include "GLStructs.h"
#include "Matrix.h"
//mat#include <glm/mat4x4.hpp>
//TODO:GL fixen,ich sehe manchmal n Dreieck
using std::vector;
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
class GLMain{

public:

	GLMain(/*void(*swapBuffersFunc)(),*/T_swapBuffersFuncType swapBuffersFunc2, T_swapBuffers_class_reference *swapBuffersFuncClass);
	void render();
	void setNumDrawElements(int count);
	void addMesh_RenderObject_struct(Mesh_RenderObject *obj, float* pass_matrix=0);
	void initGL();
	void setViewPort(GLRect rect);
	THREEDObject * draw_elements; Matrix m;
private:
	//T_swapBuffersFuncType swapBuffers;
	//void(*swapBuffers)();
	void swapBuffers();
	GLuint programId;
	GLuint * vertex_buffer,*indices_buffer,*texcoords_buffer;
	int num_draw_elements = 0;
	
	GLuint bindAttribLocation(const char* attrib_name);
	T_swapBuffers_class_reference *swap_buffers_func_class;
	T_swapBuffersFuncType swapBuffersFunc;
	template <typename T_vertices_data, typename T_indices_data>
	void addRenderElement(T_vertices_data &vertices, T_indices_data &indices, draw_method dm, int num_elements_to_draw);
	GLuint attrib_location_counter = 0;
	GLuint loc_Matrix;
	GLuint loc_Position;
	GLuint texcoord_position,diffuse_Texture_ID;

};



using namespace OGL;
/*Test functions-m�ssen entfernt werden-have tov be removed

*/
GLuint CreateSimpleTexture2D()
{
	// Texture object handle
	GLuint textureId;
	//https://code.google.com/p/opengles-book-samples/source/browse/trunk/Windows/Chapter_9/Simple_Texture2D/Simple_Texture2D.c
	// 2x2 Image, 3 bytes per pixel (R, G, B)
	GLubyte pixels[4 * 3] =
	{
		255, 0, 0, // Red
		0, 255, 0, // Green
		0, 0, 255, // Blue
		255, 255, 0  // Yellow
	};

	// Use tightly packed data
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate a texture object
	glGenTextures(1, &textureId);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, textureId);

	// Load the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	// Set the filtering mode
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return textureId;

}



template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
template <typename T_vertices_data, typename T_indices_data>//@NOTE:Hier ist die Reiheinfolge der template- (Davorschreibungen?)-wichtig,sonst meckert er,dass Deklaration und Def ungleich w�ren,lustigerweise sond sie doch gleich(nach der Anzeige),wtf
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::addRenderElement(T_vertices_data &vertices, T_indices_data &indices, draw_method dm, int num_elements_to_draw){
	THREEDObject pp;
	pp.dm = dm;
	/*const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};*/
//	pp.vertices_num = sizeof(vertices) / sizeof(GLfloat);
	pp.vertices_totalsize = sizeof(vertices);
	
	pp.vertices = new /*GL*/float[sizeof(vertices)/sizeof(float)/*vertices m�ssen glfloat sein*/];//@TODO. das hir irgendwie besser machen

	memcpy(pp.vertices, vertices, sizeof(vertices));
	if (indices != NULL){
		pp.indices_totalsize = sizeof(indices);
		pp.indices_num = sizeof(indices) / sizeof(unsigned int);
		//indices/kann auch null sein
		pp.indices = new /*GLu*/unsigned int[pp.indices_num];
		memcpy(pp.indices, indices, sizeof(indices));
		
	}
	pp.draw_call_num_elements = num_elements_to_draw;
	draw_elements[num_draw_elements] = pp;
	num_draw_elements += 1;
	

}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
GLuint GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::bindAttribLocation(const char* attrib_name){
	//https://www.opengl.org/discussion_boards/showthread.php/171837-glBindAttribLocation-after-glLinkProgram
	//muss vor glLinkProgram(damit Shader linken)aufgerufen werden,damit vor initGL
	glBindAttribLocation(programId,attrib_location_counter,attrib_name);
	attrib_location_counter++;
	return (attrib_location_counter-1);
}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::setViewPort(GLRect rect){
	glViewport(rect.x, rect.y, rect.width, rect.height);
	glScissor(rect.x,rect.y,rect.width,rect.height);
	glEnable(GL_SCISSOR_TEST);

}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::setNumDrawElements(int count){
	draw_elements = new THREEDObject[count];

}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::addMesh_RenderObject_struct(Mesh_RenderObject *obj,float* pass_matrix){
	THREEDObject pp;
	pp.dm = kElements;//@TODO:check ob indices im Mesh_RenderObject//@TODO:vllt.Auslagerung in extra Klasse
	pp.vertices_totalsize = obj->size_vertices*sizeof(float);
	pp.indices_totalsize = obj->num_indices*sizeof(unsigned int);
	pp.draw_call_num_elements = obj->num_indices /*/ 3==eigentlich faces*3-aber nur f�r Dreiecke*/;/*@TODO:�ndern*/
	pp.indices = obj->indices;
	pp.vertices = obj->vertices;
	pp.draw_primitive = obj->draw_primitive;
	//if (pass_matrix == 0){
		//pass_matrix = new float[16];
		
	//}
	
	(pass_matrix!=0 ? pp.matrix = pass_matrix:0);//@TODO:identtity matrix
	//(pass_matrix != 0) && (pp.matrix = pass_matrix);//@TODO:deees �ndern,vllt. komment tauschen
	//pp.vertices_num=obj->//@deprecated
	
	draw_elements[num_draw_elements] = pp; 
	num_draw_elements++;
}

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::GLMain(/*void(*swapBuffersFunc)(),*/ T_swapBuffersFuncType swapBuffersFunc2, T_swapBuffers_class_reference * swapBuffersFuncClass){


	programId = glCreateProgram();

	//draw_elements = new THREEDObject[2];
	//glCreateShader(GL_VERTEX_SHADER);
	//swapBuffers = swapBuffersFunc2;
	
	//T_swapBuffersFuncType sw=(swapBuffersFuncClass->*swapBuffersFunc2)();
	swap_buffers_func_class = swapBuffersFuncClass;
	swapBuffersFunc = swapBuffersFunc2;
	/*
	THREEDObject pp;
	pp.dm = kArrays;
	const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	//pp.vertices_num = sizeof(g_vertex_buffer_data) / sizeof(GLfloat);
	pp.vertices_totalsize = sizeof(g_vertex_buffer_data);
	pp.vertices = new GLfloat[pp.vertices_num];
	memcpy(pp.vertices, g_vertex_buffer_data, sizeof(g_vertex_buffer_data));
	pp.indices = NULL;
	pp.draw_call_num_elements = 0;
	num_draw_elements++;
	draw_elements[0] = pp;
	*/
	
		
	
	//initGL();
}

void determine_largest_v(float* in_out_largestV,float current_value,int i){
	
	if (i == 0){ *in_out_largestV = current_value; }
	else if (*in_out_largestV < current_value){
		*in_out_largestV = current_value;

	}

}
void determine_smallest_v(float* in_out_smallestV, float current_value, int i){

	if (i == 0){ *in_out_smallestV = current_value; }
	else if (*in_out_smallestV > current_value){
		*in_out_smallestV = current_value;

	}//@TODO:copy n paste wegm

}

/*
* @returns float[3] largest values,also 3d-Koordinaten,k�nnte theooretisch auch ne Vektor sein,ist es aber net
*/
array<array<float,3>,2> getOverallMinMax(float*verts,int num_verts){
	//zuerst max x
	//float *largest_Values= new float[3];//x,y,z
	//float *smallest_Values = new float[3];
	array<float, 3>largest_Values;
	array<float, 3>smallest_Values;
	for (int i = 0; i < num_verts; i++){
		determine_largest_v(&largest_Values[0], verts[(i * 3) + 0], i);
		determine_largest_v(&largest_Values[1], verts[(i * 3) + 1], i);
		determine_largest_v(&largest_Values[2], verts[(i * 3) + 2], i);

		determine_smallest_v(&smallest_Values[0], verts[(i * 3) + 0], i);
		determine_smallest_v(&smallest_Values[1], verts[(i * 3) + 1], i);
		determine_smallest_v(&smallest_Values[2], verts[(i * 3) + 2], i);

	}
	//float lx = largest_Values[0];
	//float ly = largest_Values[1];
	//float lz = largest_Values[2];
	array<array<float, 3>, 2> ret;
	ret[0] = largest_Values;
	ret[1] = smallest_Values;
	return ret;
}
/*
*sodass alle wohl noch im View Space sind,also NDC Range [-1;+1]
*/
float getScaleFactor(array<array<float, 3>, 2> min_max, float desired_range){
	//kleinster Wert,bisher nur x,y, ,reicht wohl auch
	//float smallest_value_x_y=largest_V[0];
	//(largest_V[1] < smallest_value_x_y) ? smallest_value_x_y = largest_V[1]:0;
	float *abstaende = new float[3];//x,y,z
	abstaende[0] = min_max[0][0] - min_max[1][0];
	abstaende[1] = min_max[0][1] - min_max[1][1];
	abstaende[2] = min_max[0][2] - min_max[1][2];
	float smallest_value_x_y = abstaende[0];
	(abstaende[1] < smallest_value_x_y) ? smallest_value_x_y = abstaende[1] : 0;
	return desired_range/smallest_value_x_y;
}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::initGL(){
	GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);
	/*
	THREEDObject pc;
	pc.dm = kElements;

float g_vertices_rectangle_data[] = {
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	0.0f, 1.0f, 1.0f,//4Eck kann man auch mittels glDrawArrays hinkriegen,auch mit 4 Vertices
	};*/
	/*float g_vertices_rectangle_data[] = {
		-1.0f, 1.0f, 0.0f,   // top left
		-1.0f, -1.0f, 0.0f,   // bottom left
		1.0f, -1.0f, 0.0f,   // bottom right
		1.0f, 1.0f, 0.0f//4Eck kann man auch mittels glDrawArrays hinkriegen,auch mit 4 Vertices
	};*/

	/*const unsigned int g_indices_data[] = {
		0, 1, 2

	};
	int size_vertices = 3;
	float* new_vertices = new float[size_vertices * 3];
	memcpy(new_vertices, g_vertices_rectangle_data, sizeof(g_vertices_rectangle_data));
	float scalefactor = getScaleFactor(getOverallMinMax(new_vertices, size_vertices), 2.0f);
	//addRenderElement(g_vertices_rectangle_data, g_indices_data, kElements, 6);
	//m = new Matrix();
	//m.scale(Vector3(scalefactor, scalefactor, scalefactor));
	//draw_elements[0].matrix = m->get_as_float16();

	/*programId = */OpenGL_Utils::LoadShaders("vertex.glsl", "fragment.glsl",programId);
	glUseProgram(programId);
	//loc_Position = 0;//bei >anzahl def. error,daher ist mit ++ am besten oder glgetattriblocation
	//glBindAttribLocation(programId, loc_Position,"vertexPosition_modelspace");
	loc_Position = bindAttribLocation("vertexPosition_modelspace");
	texcoord_position = bindAttribLocation("vertexUV");
	loc_Matrix = glGetUniformLocation(programId,"MVP");
	diffuse_Texture_ID = glGetUniformLocation(programId, "myTextureSampler");

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	vertex_buffer = new GLuint[num_draw_elements];
	indices_buffer = new GLuint[num_draw_elements];
	glGenBuffers(num_draw_elements/**2*/, vertex_buffer);
	glGenBuffers(num_draw_elements,indices_buffer);
	//int buffer_add_counter = 0;
	for (int i = 0; i < num_draw_elements; i++)
	{


		THREEDObject pc = draw_elements[i];
		// The following commands will talk about our 'vertexbuffer' buffer

		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[i]);
		//buffer_add_counter++;

		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, /*pc.vertices_num*sizeof(GLfloat)*/pc.vertices_totalsize, pc.vertices, GL_STATIC_DRAW);
		if (pc.indices != NULL){//falls nicht wird halt die 2-fache Menge an Buffern allocated//@TODO:das �ndern
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, pc.indices_totalsize, pc.indices, GL_STATIC_DRAW);
		}
		//buffer_add_counter++;
	}

	

}

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::render(){
	
	//glCreateShader(GL_VERTEX_SHADER);
	//glClearColor5(1.0f,1.0f,1.0f,1.0f);

	//Hinweis:programID wird nicht ge�ndert(opengl global), da zur Zeit keine Shaderwechsel=>Programwechsel stattfinden(typischerweise:Shader werden vorher schon vorbereitet,dann nur noch angewandt,gab mal ne Pr�sentation dazu von valva0>modern opengl-st�ndige shader-wechsel statt z.b . dauernde ifs in shadern)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(0x00004000);


	//Matrix matrix;
	//matrix.translate(Vector3(0.4f));
	//matrix.scale(Vector3(0.5f,0.5f,0.5f));
	//float *mat = matrix.get_as_float16();

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	for (int i = 0; i < num_draw_elements; i++)
	{

		//int buffer_add_counter = 0;
		THREEDObject pc = draw_elements[i];
		glUniformMatrix4fv(loc_Matrix, 1, GL_FALSE, pc.matrix);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer[i]/*testweise*/);
		glVertexAttribPointer(
			loc_Position,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset//Quelle:vermutlich opengl-tutorial.org
			);
		//buffer_add_counter++;
		// Draw Calls kommen hier
		if (pc.dm == kArrays){
			glDrawArrays(pc.draw_primitive, 0, pc.draw_call_num_elements); // 3 indices starting at 0 -> 1 triangle
		}
		else if (pc.dm == kElements){

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_buffer[i]);
			glDrawElements(pc.draw_primitive, pc.draw_call_num_elements, GL_UNSIGNED_INT, /*pc.indices*/0);

		}
		//buffer_add_counter++;
	}

	glDisableVertexAttribArray(0);


	swapBuffers();

};
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::swapBuffers(){
	(swap_buffers_func_class->*swapBuffersFunc)();

}
#endif