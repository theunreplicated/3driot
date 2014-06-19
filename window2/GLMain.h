#ifndef GL_MAIN_H
#define GL_MAIN_H
#include "OpenGLImport.h"
#include <iostream>
#include <string>
#include <fstream>
#include "OpenGL_Utils.h"
#include "GLStructs.h"

//TODO:GL fixen,ich sehe manchmal n Dreieck
using std::vector;
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
class GLMain{

public:

	GLMain(/*void(*swapBuffersFunc)(),*/T_swapBuffersFuncType swapBuffersFunc2, T_swapBuffers_class_reference *swapBuffersFuncClass);
	void render();
	void setNumDrawElements(int count);
	void addMesh_RenderObject_struct(Mesh_RenderObject *obj);
	void initGL();
	void setViewPort(GLRect rect);
private:
	//T_swapBuffersFuncType swapBuffers;
	//void(*swapBuffers)();
	void swapBuffers();
	GLuint programId;
	GLuint * vertexbuffer;
	int num_draw_elements = 0;
	THREEDObject * draw_elements;
	GLuint bindAttribLocation(const char* attrib_name);
	T_swapBuffers_class_reference *swap_buffers_func_class;
	T_swapBuffersFuncType swapBuffersFunc;
	template <typename T_vertices_data, typename T_indices_data>
	void addRenderElement(T_vertices_data &vertices, T_indices_data &indices, draw_method dm, int num_elements_to_draw);
	GLuint attrib_location_counter = 0;
	GLuint loc_Matrix;
};



using namespace OGL;

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
template <typename T_vertices_data, typename T_indices_data>//@NOTE:Hier ist die Reiheinfolge der template- (Davorschreibungen?)-wichtig,sonst meckert er,dass Deklaration und Def ungleich wären,lustigerweise sond sie doch gleich(nach der Anzeige),wtf
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
	
	pp.vertices = new /*GL*/float[sizeof(vertices)/sizeof(float)/*vertices müssen glfloat sein*/];//@TODO. das hir irgendwie besser machen

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

}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::setViewPort(GLRect rect){
	glViewport(rect.x,rect.y,rect.width,rect.height);

}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::setNumDrawElements(int count){
	draw_elements = new THREEDObject[count];

}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::addMesh_RenderObject_struct(Mesh_RenderObject *obj){
	THREEDObject pp;
	pp.dm = kElements;//@TODO:check ob indices im Mesh_RenderObject//@TODO:vllt.Auslagerung in extra Klasse
	pp.vertices_totalsize = obj->size_vertices*sizeof(float);
	pp.indices_totalsize = obj->num_indices*sizeof(unsigned int);
	pp.draw_call_num_elements = obj->num_indices /*/ 3==eigentlich faces*3*/;/*@TODO:ändern*/
	pp.indices = obj->indices;
	pp.vertices = obj->vertices;
	pp.draw_primitive = obj->draw_primitive;
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
	
		THREEDObject pc;
	pc.dm = kElements;
	
	float g_vertices_rectangle_data[] = {
		-0.5f, 0.5f, 0.0f,   // top left
		-0.5f, -0.5f, 0.0f,   // bottom left
		0.5f, -0.5f, 0.0f,   // bottom right
		0.5f, 0.5f, 0.0f//4Eck kann man auch mittels glDrawArrays hinkriegen,auch mit 4 Vertices
	};

	const unsigned int g_indices_data[] = {
		0, 1, 2, 0, 2, 3

	};

	//addRenderElement(g_vertices_rectangle_data,g_indices_data,kElements,6);
	
	//initGL();
}

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::initGL(){
	GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);
	
	/*programId = */OpenGL_Utils::LoadShaders("vertex.glsl", "fragment.glsl",programId);
	glUseProgram(programId);
	loc_Matrix = glGetUniformLocation(programId,"MVP");
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	vertexbuffer = new GLuint[num_draw_elements];
	glGenBuffers(num_draw_elements*2, vertexbuffer);
	int buffer_add_counter = 0;
	for (int i = 0; i < num_draw_elements; i++)
	{


		THREEDObject pc = draw_elements[i];
		// The following commands will talk about our 'vertexbuffer' buffer

		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[buffer_add_counter]);
		buffer_add_counter++;

		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, /*pc.vertices_num*sizeof(GLfloat)*/pc.vertices_totalsize, pc.vertices, GL_STATIC_DRAW);
		if (pc.indices != NULL){//falls nicht wird halt die 2-fache Menge an Buffern allocated//@TODO:das ändern
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexbuffer[buffer_add_counter]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, pc.indices_totalsize, pc.indices, GL_STATIC_DRAW);
		}
		buffer_add_counter++;
	}

	

}

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::render(){
	
	//glCreateShader(GL_VERTEX_SHADER);
	//glClearColor5(1.0f,1.0f,1.0f,1.0f);

	//Hinweis:programID wird nicht geändert(opengl global), da zur Zeit keine Shaderwechsel=>Programwechsel stattfinden(typischerweise:Shader werden vorher schon vorbereitet,dann nur noch angewandt,gab mal ne Präsentation dazu von valva0>modern opengl-ständige shader-wechsel statt z.b . dauernde ifs in shadern)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(0x00004000);
	float* mat = new float[16];
	mat[0] = 1.0f;
	mat[1] = 0.0f;
	mat[2] = 0.0f;
	mat[3] = 0.0f;
	//=identity matrix
	mat[4] = 0.0f;
	mat[5] = 1.0f;
	mat[6] = 0.0f;
	mat[7] = 0.0f;

	mat[8] = 0.0f;
	mat[9] = 0.0f;
	mat[10] = 1.0f;
	mat[11] = 0.0f;

	mat[12] = 0.0f;
	mat[13] = 0.0f;
	mat[14] = 0.0f;
	mat[15] = 1.0f;
	glUniformMatrix4fv(loc_Matrix,1,GL_FALSE,mat);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	for (int i = 0; i < num_draw_elements; i++)
	{

		int buffer_add_counter = 0;
		THREEDObject pc = draw_elements[i];
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[buffer_add_counter]/*testweise*/);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset//Quelle:vermutlich opengl-tutorial.org
			);
		buffer_add_counter++;
		// Draw the triangle !
		if (pc.dm == kArrays){
			glDrawArrays(pc.draw_primitive, 0, pc.draw_call_num_elements); // 3 indices starting at 0 -> 1 triangle
		}
		else if (pc.dm == kElements){

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexbuffer[buffer_add_counter]);
			glDrawElements(pc.draw_primitive, pc.draw_call_num_elements, GL_UNSIGNED_INT, /*pc.indices*/0);

		}
		buffer_add_counter++;
	}

	glDisableVertexAttribArray(0);


	swapBuffers();

};
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::swapBuffers(){
	(swap_buffers_func_class->*swapBuffersFunc)();

}
#endif