#ifndef GL_MAIN_H
#define GL_MAIN_H
#include "OpenGLImport.h"
#include <iostream>
#include <string>
#include <fstream>
#include "OpenGL_Utils.h"
//#include "GLStructs.h"
#include "Matrix.h"
#include "WindowStructs.h"
#include "Import_Object_Struct.h"
#include <glm\mat4x4.hpp>
//mat#include <glm/mat4x4.hpp>
using std::vector;
typedef Windows::WindowRect GLRect;
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
class GLMain{

public:

	GLMain(/*void(*swapBuffersFunc)(),*/T_swapBuffersFuncType swapBuffersFunc2, T_swapBuffers_class_reference *swapBuffersFuncClass,bool use_legacy_system_opengl);
	void render();
	//void setNumDrawElements(int count);
	void addMesh_RenderObject_struct(Mesh_RenderObject *obj, float* pass_matrix=0);
	void initGL();
	void setViewPort(GLRect rect);
	std::vector<T_DRAW_STRUCTURE> draw_elements;
	//THREEDObject * draw_elements; 
	//Matrix m;
	//int num_draw_elements = 0;
	void add_to_buffer_and_add_to_draw_list(Mesh_RenderObject *obj, float* pass_matrix=0);
	void setCameraMatrix(glm::mat4 matrix);
	void setCameraTransformMatrix(glm::mat4 matrix);
	void setProjectionMatrix(glm::mat4 matrix);
private:
	//T_swapBuffersFuncType swapBuffers;
	//void(*swapBuffers)();
	void swapBuffers();
	GLuint programId;
	//GLuint * vertex_buffer,*indices_buffer,*texcoords_buffer;
	//GLuint * Diffuse_Texture_IDs;
	//std::vector<GLuint> vertex_buffer, indices_buffer, texcoords_buffer, Diffuse_Texture_IDs;

	GLuint bindAttribLocation(const char* attrib_name);
	T_swapBuffers_class_reference *swap_buffers_func_class;
	T_swapBuffersFuncType swapBuffersFunc;
	//template <typename T_vertices_data, typename T_indices_data>
	//void addRenderElement(T_vertices_data &vertices, T_indices_data &indices, draw_method dm, int num_elements_to_draw);
	GLuint attrib_location_counter = 0;
	GLuint loc_Matrix;
	GLuint loc_Position;
	GLuint texcoord_position,diffuse_Texture_sample_Loc;
	void fillBuffer(T_DRAW_STRUCTURE& pc);
	GLuint loadTexture(T_DRAW_STRUCTURE*mesh_data);
	glm::mat4 /*proj_camera_matrix,*/ camera_transform_matrix, camera_matrix, projection_matrix;
	bool m_use_legacy_system_opengl;
	bool use_vp_matrix;

};



using namespace OGL;
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

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::setCameraTransformMatrix(glm::mat4 matrix){
	//proj_camera_matrix = matrix;
	//use_vp_matrix = true;
	camera_transform_matrix = matrix;

}

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::setCameraMatrix(glm::mat4 matrix){
	camera_matrix = matrix;
	//use_vp_matrix = true;

}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::setProjectionMatrix(glm::mat4 matrix){
	//camera_matrix = matrix;
	projection_matrix = matrix;
	//use_vp_matrix = true;

}


template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
GLuint GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference,T_DRAW_STRUCTURE>::bindAttribLocation(const char* attrib_name){
	//https://www.opengl.org/discussion_boards/showthread.php/171837-glBindAttribLocation-after-glLinkProgram
	//muss vor glLinkProgram(damit Shader linken)aufgerufen werden,damit vor initGL
	glBindAttribLocation(programId,attrib_location_counter,attrib_name);
	attrib_location_counter++;
	return (attrib_location_counter-1);
}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference,T_DRAW_STRUCTURE>::setViewPort(GLRect rect){
	glViewport(rect.x, rect.y, rect.width, rect.height);
	glScissor(rect.x,rect.y,rect.width,rect.height);
	glEnable(GL_SCISSOR_TEST);//@TODO:Check ob scissor_test oder glscissor,ich denke eher net

}
//@deprecated
/*template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::setNumDrawElements(int count){
	draw_elements = new THREEDObject[count];

}*/
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference,T_DRAW_STRUCTURE>::addMesh_RenderObject_struct(Mesh_RenderObject *obj, float* pass_matrix){
	T_DRAW_STRUCTURE pp;
	pp.dm = kElements;//@TODO:check ob indices im Mesh_RenderObject//@TODO:vllt.Auslagerung in extra Klasse
	pp.vertices_totalsize = obj->size_vertices*sizeof(float);
	//size_t khrzt = sizeof(float);
	//size_t khkk = sizeof(obj->size_vertices);
	pp.texcoords_totalsize = obj->num_tex_coords*sizeof(float);
	pp.indices_totalsize = obj->num_indices*sizeof(unsigned int);
	pp.draw_call_num_elements = obj->num_indices /*/ 3==eigentlich faces*3-aber nur für Dreiecke*/;/*@TODO:ändern*/
	pp.indices = obj->indices;
	pp.vertices = obj->vertices;
	pp.draw_primitive = obj->draw_primitive;
	pp.has_tex_coord = obj->has_tex_coord;
	pp.tex_coords = obj->tex_coords;
	pp.texture_data = obj->texture_data;
	pp.has_texture =obj->has_texture;
	
	//if (pass_matrix == 0){
		//pass_matrix = new float[16];
		
	//}
	
	(pass_matrix!=0 ? pp.matrix = pass_matrix:0);//@TODO:identtity matrix
	//(pass_matrix != 0) && (pp.matrix = pass_matrix);//@TODO:deees ändern,vllt. komment tauschen
	//pp.vertices_num=obj->//@deprecated
	
	draw_elements.push_back(pp);
	//draw_elements[num_draw_elements] = pp; 
	//num_draw_elements++;
}

 
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::GLMain(/*void(*swapBuffersFunc)(),*/ T_swapBuffersFuncType swapBuffersFunc2, T_swapBuffers_class_reference * swapBuffersFuncClass, bool use_legacy_system_opengl){


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
	
	m_use_legacy_system_opengl = use_legacy_system_opengl;
	
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
* @returns float[3] largest values,also 3d-Koordinaten,könnte theooretisch auch ne Vektor sein,ist es aber net
*/
/*
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
}*/
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
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
GLuint GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::loadTexture(T_DRAW_STRUCTURE*mesh_data){
	GLuint textureID;
	
	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	
	//int test_ret = mesh_data->texture_data.width;
	// Load the texture
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	/*GLenum texture_type=GL_RGBA;
	if (mesh_data->texture_data.color_type == ColorData_RGB){
		GLenum texture_type = GL_RGB;

	}
	else if (mesh_data->texture_data.color_type == ColorData_RGBA){
		GLenum texture_type = GL_RGBA;

	}
	else{
		//@TODO:loggen,falls undefiniert

	}*/
	//int *testvp = mesh_data->texture_data.test;
	//int textvar = *testvp;

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mesh_data->texture_data.width, mesh_data->texture_data.height, 0,/* mesh_data->texture_data.format*/GL_RGBA, GL_UNSIGNED_BYTE,/*mesh_data->texture_data.bits*/(void*)mesh_data->texture_data.texture_bytes);
	glTexImage2D(GL_TEXTURE_2D, 0, mesh_data->texture_data.format, mesh_data->texture_data.width, mesh_data->texture_data.height, 0, mesh_data->texture_data.format, GL_UNSIGNED_BYTE, mesh_data->texture_data.bits);
	//mesh_data->texture_data.unload();//muss man nicht unbedingt machen
	//@TODO:unload sollte klappen,keine access violation
	/*
	 // ... nice trilinear filtering.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
        glGenerateMipmap(GL_TEXTURE_2D);
das kommt da normalerweise hin
	*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	return textureID;
}

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::add_to_buffer_and_add_to_draw_list(Mesh_RenderObject *obj, float* pass_matrix){
	addMesh_RenderObject_struct(obj, pass_matrix);
	T_DRAW_STRUCTURE * d = &draw_elements.back();
	fillBuffer(*d);

}

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference,T_DRAW_STRUCTURE>::fillBuffer(T_DRAW_STRUCTURE& pc){

	glGenBuffers(1, &pc.vertex_buffer);
	if (pc.indices != NULL){
		glGenBuffers(1, &pc.indices_buffer);
	}
	if (pc.has_tex_coord){
		glGenBuffers(1, &pc.texcoords_buffer);
	}
	//THREEDObject pc = draw_elements[i];


	if (pc.has_texture){
		pc.Diffuse_Texture_IDs = loadTexture(&pc);
	}


	glBindBuffer(GL_ARRAY_BUFFER, pc.vertex_buffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, /*pc.vertices_num*sizeof(GLfloat)*/pc.vertices_totalsize, pc.vertices, GL_STATIC_DRAW);
	if (pc.indices != NULL){//falls nicht wird halt die 2-fache Menge an Buffern allocated//@TODO:das ändern
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pc.indices_buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, pc.indices_totalsize, pc.indices, GL_STATIC_DRAW);
	}
	if (pc.has_tex_coord){
		glBindBuffer(GL_ARRAY_BUFFER, pc.texcoords_buffer);
		// Give our vertices to OpenGL.
		glBufferData(GL_ARRAY_BUFFER, /*pc.vertices_num*sizeof(GLfloat)*/pc.texcoords_totalsize, pc.tex_coords, GL_STATIC_DRAW);

	}

}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference,T_DRAW_STRUCTURE>::initGL(){
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
	
	/*programId = */
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	OpenGL_Utils::LoadShaders(m_use_legacy_system_opengl,programId);
	glUseProgram(programId);
	//loc_Position = 0;//bei >anzahl def. error,daher ist mit ++ am besten oder glgetattriblocation
	//glBindAttribLocation(programId, loc_Position,"vertexPosition_modelspace");
	loc_Position = bindAttribLocation("vertexPosition_modelspace");//@TODO:check ob wirklich vor loadShaders/
	texcoord_position = bindAttribLocation("vertexUV");
	loc_Matrix = glGetUniformLocation(programId,"MVP");
	diffuse_Texture_sample_Loc = glGetUniformLocation(programId, "myTextureSampler");
	//Diffuse_Texture_ID = loadTexture();
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	//vertex_buffer = new GLuint[num_draw_elements];
	//indices_buffer = new GLuint[num_draw_elements];
	//texcoords_buffer = new GLuint[num_draw_elements];
	//glGenBuffers(num_draw_elements/**2*/, vertex_buffer);
	//glGenBuffers(num_draw_elements,indices_buffer);
	//glGenBuffers(num_draw_elements,texcoords_buffer);
	//Diffuse_Texture_IDs = new GLuint[num_draw_elements];//@TODO:es werden alle Dingens geaddet,nicht aber nur die,die ne Texture haben
	//int buffer_add_counter = 0;
	
	for (T_DRAW_STRUCTURE& pc: draw_elements)
	{

		fillBuffer(pc);
	}

	

}

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::render(){
	
	//glCreateShader(GL_VERTEX_SHADER);
	//glClearColor5(1.0f,1.0f,1.0f,1.0f);
	//@note normalerweise vorher gluseprogram,ein program müsste im moment reichen,da kein Wechsel,auch net brnötig
	//Hinweis:programID wird nicht geändert(opengl global), da zur Zeit keine Shaderwechsel=>Programwechsel stattfinden(typischerweise:Shader werden vorher schon vorbereitet,dann nur noch angewandt,gab mal ne Präsentation dazu von valva0>modern opengl-ständige shader-wechsel statt z.b . dauernde ifs in shadern)
#ifndef UNSCHOENER_STIL_BACKGROUND_COLOR_BLACK
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
#else
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
#endif

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	//Matrix matrix;
	//matrix.translate(Vector3(0.4f));
	//matrix.scale(Vector3(0.5f,0.5f,0.5f));
	//float *mat = matrix.get_as_float16();
	 
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(loc_Position);//@TODO:gucken ob hierhin oder in die For-SChleife,disalb emuss nach dem draw-call kommen
	for (T_DRAW_STRUCTURE& pc : draw_elements)
	{

		//int buffer_add_counter = 0;
		//THREEDObject pc = draw_elements[i];
		glm::mat4 m = glm::make_mat4(pc.matrix);
		//@TODO:das mit dem camera_transformmatrix ist wohl nicht richtigso ,gehört wohl alles in den camera aka view matrix
		//glm::mat4 res = proj_camera_matrix*m;
		glm::mat4 res = projection_matrix*camera_matrix*camera_transform_matrix;
		glUniformMatrix4fv(loc_Matrix, 1, GL_FALSE,glm::value_ptr(res) );

		if (pc.has_texture){
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, pc.Diffuse_Texture_IDs);
			// Set our "myTextureSampler" sampler to user Texture Unit 0
			glUniform1i(diffuse_Texture_sample_Loc, 0);//kann man wohl mit active texture zusammen nach oben schiebn(aus der for-schleife heraus)
		}

		//position vertex hinschieben
		glBindBuffer(GL_ARRAY_BUFFER,pc.vertex_buffer/*testweise*/);
		glVertexAttribPointer(
			loc_Position,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset//Quelle:vermutlich opengl-tutorial.org
			);
		

		glEnableVertexAttribArray(texcoord_position);//@TODO:gucken ob auch in if-Anweisung
		if (pc.has_tex_coord){
			glBindBuffer(GL_ARRAY_BUFFER, pc.texcoords_buffer);
			glVertexAttribPointer(
				texcoord_position,                                // attribute. No particular reason for 1, but must match the layout in the shader.
				2,                                // size : U+V => 2
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
				);

		}



		// Draw Calls kommen hier
		if (pc.dm == kArrays){
			glDrawArrays(pc.draw_primitive, 0, pc.draw_call_num_elements); // 3 indices starting at 0 -> 1 triangle
		}
		else if (pc.dm == kElements){

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pc.indices_buffer);
			glDrawElements(pc.draw_primitive, pc.draw_call_num_elements, GL_UNSIGNED_INT, /*pc.indices*/0);

		}
		//bei kinvisible passiert wohl nichts
		//buffer_add_counter++;
	}

	glDisableVertexAttribArray(loc_Position);
	glDisableVertexAttribArray(texcoord_position);

	swapBuffers();

};
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference,T_DRAW_STRUCTURE>::swapBuffers(){
	(swap_buffers_func_class->*swapBuffersFunc)();

}
#endif