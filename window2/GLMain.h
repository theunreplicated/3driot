#ifndef GL_MAIN_H
#define GL_MAIN_H
#include "OpenGLImport.h"
#include <iostream>
#include <string>
#include <fstream>
enum draw_method{ kArrays, kElements };//konstant davor,falls Konflikte

struct THREEDObject{
	draw_method dm;
	GLfloat * vertices;
	GLuint * indices;//nur falls Elemente
	int vertices_num, indices_num/*könnte man eigentlich streichen*/;
	int draw_call_num_elements;
	size_t vertices_totalsize,indices_totalsize;
};
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
class GLMain{

public:

	GLMain(/*void(*swapBuffersFunc)(),*/T_swapBuffersFuncType swapBuffersFunc2, T_swapBuffers_class_reference *swapBuffersFuncClass);
	void render();
private:
	//T_swapBuffersFuncType swapBuffers;
	//void(*swapBuffers)();
	void swapBuffers();
	void initGL();
	GLuint * vertexbuffer;
	int num_draw_elements = 0;
	THREEDObject * draw_elements;
	T_swapBuffers_class_reference *swap_buffers_func_class;
	T_swapBuffersFuncType swapBuffersFunc;
	template <typename T_vertices_data, typename T_indices_data>
	void addRenderElement(T_vertices_data &vertices, T_indices_data &indices, draw_method dm, int num_elements_to_draw);
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
	
	pp.vertices = new GLfloat[sizeof(vertices)/sizeof(GLfloat)/*vertices müssen glfloat sein*/];//@TODO. das hir irgendwie besser machen

	memcpy(pp.vertices, vertices, sizeof(vertices));
	if (indices != NULL){
		pp.indices_num = sizeof(indices) / sizeof(T_indices_data);
		//indices/kann auch null sein
		pp.indices = new GLuint[pp.indices_num];
		memcpy(pp.indices, indices, sizeof(indices));
		
	}
	pp.draw_call_num_elements = num_elements_to_draw;
	draw_elements[num_draw_elements] = pp;
	num_draw_elements += 1;
	

}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::GLMain(/*void(*swapBuffersFunc)(),*/ T_swapBuffersFuncType swapBuffersFunc2, T_swapBuffers_class_reference * swapBuffersFuncClass){

	draw_elements = new THREEDObject[2];
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
	
	const GLfloat g_vertices_rectangle_data[] = {
		-0.5f, 0.5f, 0.0f,   // top left
		-0.5f, -0.5f, 0.0f,   // bottom left
		0.5f, -0.5f, 0.0f,   // bottom right
		0.5f, 0.5f, 0.0f//4Eck kann man auch mittels glDrawArrays hinkriegen,auch mit 4 Vertices
	};

	const GLuint g_indices_data[] = {
		0, 1, 2, 0, 2, 3

	};
	/*pc.vertices_num = sizeof(g_vertices_rectangle_data) / sizeof(GLfloat);
	pc.vertices = new GLfloat[pc.vertices_num];
	memcpy(pc.vertices, g_vertices_rectangle_data, sizeof(g_vertices_rectangle_data));
	pc.indices_num = sizeof(g_indices_data) / sizeof(GLuint);
	pc.indices = new GLuint[pc.indices_num];
	memcpy(pc.indices, g_indices_data, sizeof(g_indices_data));
	//pc.indices = &g_indices_data;
	pc.draw_call_num_elements = 6;
	num_draw_elements += 1;
	draw_elements[1] = pc;
	*/
	addRenderElement(g_vertices_rectangle_data,g_indices_data,kElements,6);

	initGL();
}
GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path){
	GLenum GL_VERTEX_SHADER = 0x8B31;

	GLenum GL_FALSE = 0;
	GLenum GL_FRAGMENT_SHADER = 0x8B30;//https://chromium.googlesource.com/angle/angle/+/master/include/GLES2/gl2.h
	GLenum  GL_LINK_STATUS = 0x8B82;
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()){
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// Compile Vertex Shader
	// printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	//glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	//glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	// std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	//glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	//fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

	// Compile Fragment Shader
	// printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	//glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	// glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	//std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	//glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	//fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

	// Link the program
	//fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	//glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	// glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	//std::vector<char> ProgramErrorMessage( max(InfoLogLength, int(1)) );
	//glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	//fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::initGL(){
	GLenum GL_ARRAY_BUFFER = 0x8892;//TODO merge zu einem
	GLenum GL_STATIC_DRAW = 0x88E4;
	GLuint VertexArrayID;
	//glGenVertexArrays(1, &VertexArrayID);
	//glBindVertexArray(VertexArrayID);
	GLuint programId = LoadShaders("vertex.glsl", "fragment.glsl");


	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	vertexbuffer = new GLuint[num_draw_elements];
	glGenBuffers(num_draw_elements, vertexbuffer);
	for (int i = 0; i < num_draw_elements; i++)
	{


		THREEDObject pc = draw_elements[i];
		// The following commands will talk about our 'vertexbuffer' buffer
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[i]);

		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, /*pc.vertices_num*sizeof(GLfloat)*/pc.vertices_totalsize, pc.vertices, GL_STATIC_DRAW);
	}

	glUseProgram(programId);

}

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::render(){
	GLenum GL_UNSIGNED_INT = 0x1405;
	GLenum GL_UNSIGNED_SHORT = 0x1403;
	GLenum GL_ARRAY_BUFFER = 0x8892;//TODO merge zu einem
	GLenum GL_STATIC_DRAW = 0x88E4;
	GLenum GL_FALSE = 0;
	GLenum GL_FLOAT = 0x1406;
	GLenum GL_TRIANGLES = 0x0004;
	//glCreateShader(GL_VERTEX_SHADER);
	//glClearColor5(1.0f,1.0f,1.0f,1.0f);

	//Hinweis:programID wird nicht geändert(opengl global), da zur Zeit keine Shaderwechsel=>Programwechsel stattfinden(typischerweise:Shader werden vorher schon vorbereitet,dann nur noch angewandt,gab mal ne Präsentation dazu von valva0>modern opengl-ständige shader-wechsel statt z.b . dauernde ifs in shadern)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(0x00004000);


	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	for (int i = 0; i < num_draw_elements; i++)
	{


		THREEDObject pc = draw_elements[i];
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[i]/*testweise*/);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		// Draw the triangle !
		if (pc.dm == kArrays){
			glDrawArrays(GL_TRIANGLES, 0, pc.draw_call_num_elements); // 3 indices starting at 0 -> 1 triangle
		}
		else if (pc.dm == kElements){
			glDrawElements(GL_TRIANGLES, pc.draw_call_num_elements, GL_UNSIGNED_INT, pc.indices);

		}
	}

	glDisableVertexAttribArray(0);


	swapBuffers();

};
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::swapBuffers(){
	(swap_buffers_func_class->*swapBuffersFunc)();

}
#endif