#ifndef INC_GLMain_CPP
#define INC_GLMain_CPP
#include <string>
#include <fstream>
#include "OpenGLImport.h"
//#include "GLStructs.h"
//#include "Matrix.h"
#include "../window2/WindowStructs.h"
#include "../window2/Import_Object_Struct.h"
#include <glm\mat4x4.hpp>
using namespace OGL;
#include "../window2/GLMain.h"
#include "resource.h"
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
GLuint GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::bindAttribLocation(const char* attrib_name){
	//https://www.opengl.org/discussion_boards/showthread.php/171837-glBindAttribLocation-after-glLinkProgram
	//muss vor glLinkProgram(damit Shader linken)aufgerufen werden,damit vor initGL
	glBindAttribLocation(m_current_program->m_program_id, m_current_program->attrib_location_counter, attrib_name);
	m_current_program->attrib_location_counter++;
	return (m_current_program->attrib_location_counter - 1);
}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::setViewPort(GLRect rect){
	glViewport(rect.x, rect.y, rect.width, rect.height);
	width = rect.width; height = rect.height;
	//glScissor(rect.x,rect.y,rect.width,rect.height);
	//glEnable(GL_SCISSOR_TEST);//@TODO:Check ob scissor_test oder glscissor,ich denke eher net

}
//@deprecated
/*template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference>::setNumDrawElements(int count){
draw_elements = new THREEDObject[count];

}*/
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::addMesh_RenderObject_struct(Mesh_RenderObject *obj, float* pass_matrix){
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
	pp.has_texture = obj->has_texture;
	pp.enable_matrix = true;//einfach auf true setzen@TODO:so nicht
	//if (pass_matrix == 0){
	//pass_matrix = new float[16];

	//}

	if (pass_matrix != 0){
		pp.matrix = glm::make_mat4(pass_matrix);

	}
	//@TODO:identtity matrix
	//(pass_matrix != 0) && (pp.matrix = pass_matrix);//@TODO:deees ändern,vllt. komment tauschen
	//pp.vertices_num=obj->//@deprecated

	draw_elements.push_back(pp);
	//draw_elements[num_draw_elements] = pp; 
	//num_draw_elements++;
}

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::set_current_program(GL_Program* program){
	m_current_program = program; glUseProgram(program->m_program_id);

	loc_Position = bindAttribLocation("vertexPosition_modelspace");//@TODO:check ob wirklich vor loadShaders/
	texcoord_position = bindAttribLocation("vertexUV");//@TODO:rename von bindattriblocation
	loc_Matrix = glGetUniformLocation(m_current_program->m_program_id, "MVP");
	diffuse_Texture_sample_Loc = glGetUniformLocation(m_current_program->m_program_id, "myTextureSampler");


}

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::GLMain(/*void(*swapBuffersFunc)(),*/ T_swapBuffersFuncType swapBuffersFunc2, T_swapBuffers_class_reference * swapBuffersFuncClass, bool use_legacy_system_opengl){
	//	programId = glCreateProgram555();

//	programId = glCreateProgram();

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
/*
void determine_largest_v(float* in_out_largestV, float current_value, int i){

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
*/

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


/*float getScaleFactor(array<array<float, 3>, 2> min_max, float desired_range){
	//kleinster Wert,bisher nur x,y, ,reicht wohl auch
	//float smallest_value_x_y=largest_V[0];
	//(largest_V[1] < smallest_value_x_y) ? smallest_value_x_y = largest_V[1]:0;
	float *abstaende = new float[3];//x,y,z
	abstaende[0] = min_max[0][0] - min_max[1][0];
	abstaende[1] = min_max[0][1] - min_max[1][1];
	abstaende[2] = min_max[0][2] - min_max[1][2];
	float smallest_value_x_y = abstaende[0];
	(abstaende[1] < smallest_value_x_y) ? smallest_value_x_y = abstaende[1] : 0;
	return desired_range / smallest_value_x_y;
}*/
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::set_framebuffer_to_position(bool to_offscreen_position){
	glBindFramebuffer(GL_FRAMEBUFFER, to_offscreen_position ? ID_framebuffer : 0);

}


template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::create_and_bind_framebuffer(){
	//GLuint framebuffer;
	glGenFramebuffers(1, &ID_framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, ID_framebuffer);


}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::create_color_renderbuffer(){
	glGenRenderbuffers(1, &colorRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA8, width, height);//kann sein,dass rgba besser ist
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);

}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::create_depth_renderbuffer(){
	glGenRenderbuffers(1, &depthRenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);

	//kann sein,dass nicht nötig
}template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
char * GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>:: getErrorType(const GLenum errorno){
	switch (errorno)
	{
	case GL_NO_ERROR:return "no error";
	case GL_INVALID_ENUM:return "invalid enum";
	case GL_INVALID_VALUE: return "invalid value";
	case GL_INVALID_OPERATION:return "invalid operation";
	case GL_OUT_OF_MEMORY:return "out of memory";
	default:
		return "unknown error";
	}

}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
template <typename T_Gl_typ>
T_Gl_typ  * GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::get_pixels_at_position(int pos_x, int pos_y, GLenum format, GLenum type, int width, int height){
	//bei jedem swapbuffers wird der Inhalt des aktuellen buffers geleert,daher greift glreadpixels auf nichts zu ,Lösung:vorher abspeichern
	//@TODO: http://lektiondestages.blogspot.de/2013/01/reading-opengl-backbuffer-to-system.html
	//http://stackoverflow.com/questions/6789655/glreadpixels-fails-to-fill-bytebuffer
	//http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-14-render-to-texture/
	//http://www.swiftless.com/tutorials/opengl/framebuffer.html
	//http://www.songho.ca/opengl/gl_pbo.html
	//http://books.google.de/books?id=odgdAAAAQBAJ&pg=PA429&lpg=PA429&dq=opengl+framebuffer+glreadpixels&source=bl&ots=waKxG_dWK9&sig=K0NtcYoDSojX3HtEcnHR9ep_Eck&hl=de&sa=X&ei=0rj3U9-EJ8vaaJjkgfAL&ved=0CC0Q6AEwAjgK#v=onepage&q=opengl%20framebuffer%20glreadpixels&f=false
	//http://en.wikibooks.org/wiki/OpenGL_Programming/Object_selection
	//http://www.opengl.org/wiki/Framebuffer_Object_Examples#glReadPixels
	//PBO wurden erst in GLES 3.0 hinzugefügt !!!!!,aber bin nichts ischer ob das gebrauch twird
	//http://stackoverflow.com/questions/18782351/opengl-es2-0-glreadpixels-read-data-from-renderbuffer-through-framebuffer
	//https://developer.apple.com/library/ios/documentation/3ddrawing/conceptual/opengles_programmingguide/WorkingwithEAGLContexts/WorkingwithEAGLContexts.html
	const GLenum component = 4;
	T_Gl_typ * pixels = new T_Gl_typ[4 * width*height];
	glReadPixels(pos_x, pos_y, width, height, format, type, pixels); 
	const GLenum error=glGetError();
	//char*err = getErrorType(error);//@TODO:soll gehen
	return pixels;
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
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::TEST_restore_dummy_texture(){

	draw_elements = TEST_orig_draw_elements_for_restoring;
}

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::TEST_create_dummy_texture(){
	unsigned char * texture_bits = new unsigned char[3];
	int texture_bits_2_id = 0;
	texture_bits[0] = 255; texture_bits[1] = 0; texture_bits[2] = texture_bits_2_id;// texture_bits[3] = 1;
	T_DRAW_STRUCTURE ppp;
	ppp.texture_data.bits = texture_bits; ppp.texture_data.format = GL_RGB; ppp.texture_data.width = 1; ppp.texture_data.height = 1;
	TEST_orig_draw_elements_for_restoring = draw_elements;
	for (T_DRAW_STRUCTURE& pc : draw_elements)
	{

		pc.Diffuse_Texture_IDs = loadTexture(&ppp);

		texture_bits[2] = ++texture_bits_2_id;
	}
}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::fillBuffer(T_DRAW_STRUCTURE& pc){

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
	if (pc.indices != NULL/*nullptr*/){//falls nicht wird halt die 2-fache Menge an Buffern allocated//@TODO:das ändern
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
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::initGL(){
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
	//glDepthFunc(GL_LEQUAL);//@TODO:gucken ob ich das vllt. doch besser nicht auskommentiere
	GL_Program*gp = new GL_Program();

	glDepthMask(GL_TRUE);
	glDepthRangef(0.0, 1.0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//@TODO:Problem depth test:anweisung konfigureiren wie hier:http://www.opengl.org/wiki/Depth_Buffer
	//	OpenGL_Utils::LoadShaders(m_use_legacy_system_opengl, programId);
	//Shader_Source sc();//gefährlich@TODO:gucken
	Shader_Source*sc = new Shader_Source((m_use_legacy_system_opengl ? { IDR_MYVERTEXSHADER, VERTEX_SHADER_PATH } : {IDR_MYVERTEXSHADER_ESSL, VERTEX_SHADER_PATH_ESSL}),
		(m_use_legacy_system_opengl ? { IDR_MYFRAGMENTSHADER, FRAGMENT_SHADER_PATH } : {IDR_MYFRAGMENTSHADER_ESSL, FRAGMENT_SHADER_PATH_ESSL}) );
	gp->assign_shaders(sc->setup_for_usage_by_program());
	//glUseProgram(programId);
	//loc_Position = 0;//bei >anzahl def. error,daher ist mit ++ am besten oder glgetattriblocation
	//glBindAttribLocation(programId, loc_Position,"vertexPosition_modelspace");
	
	set_current_program(gp);
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

	for (T_DRAW_STRUCTURE& pc : draw_elements)
	{

		fillBuffer(pc);
	}


	create_and_bind_framebuffer();
	create_color_renderbuffer();
	create_depth_renderbuffer();
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		::MessageBox(NULL, "dsa", "fd", MB_OK);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::render(bool swap_the_Buffers){

	//glCreateShader(GL_VERTEX_SHADER);
	//glClearColor5(1.0f,1.0f,1.0f,1.0f);
	//@note normalerweise vorher gluseprogram,ein program müsste im moment reichen,da kein Wechsel,auch net brnötig
	//Hinweis:programID wird nicht geändert(opengl global), da zur Zeit keine Shaderwechsel=>Programwechsel stattfinden(typischerweise:Shader werden vorher schon vorbereitet,dann nur noch angewandt,gab mal ne Präsentation dazu von valva0>modern opengl-ständige shader-wechsel statt z.b . dauernde ifs in shadern)

#ifndef UNSCHOENER_STIL_BACKGROUND_COLOR_BLACK
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
#else
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepthf(1.0);

	//Matrix matrix;
	//matrix.translate(Vector3(0.4f));
	//matrix.scale(Vector3(0.5f,0.5f,0.5f));
	//float *mat = matrix.get_as_float16();

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(loc_Position);//@TODO:gucken ob hierhin oder in die For-SChleife,disalb emuss nach dem draw-call kommen
	//int i = 0;
	for (T_DRAW_STRUCTURE& pc : draw_elements)
	{
		//i++;
		//if (i == 1){ 
		//	continue; 
		//}

		//int buffer_add_counter = 0;
		//THREEDObject pc = draw_elements[i];
		glm::mat4 m = /*glm::make_mat4(*/pc.matrix/*)*/;
		//@TODO:das mit dem camera_transformmatrix ist wohl nicht richtigso ,gehört wohl alles in den camera aka view matrix
		//glm::mat4 res = proj_camera_matrix*m;
		glm::mat4 res = projection_matrix*camera_matrix*/*camera_transform_matrix*/m;
		glUniformMatrix4fv(loc_Matrix, 1, GL_FALSE, glm::value_ptr(res));

		if (pc.has_texture){
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, pc.Diffuse_Texture_IDs);
			// Set our "myTextureSampler" sampler to user Texture Unit 0
			glUniform1i(diffuse_Texture_sample_Loc, 0);//kann man wohl mit active texture zusammen nach oben schiebn(aus der for-schleife heraus)
		}

		//position vertex hinschieben
		glBindBuffer(GL_ARRAY_BUFFER, pc.vertex_buffer/*testweise*/);
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
			glVertexAttribPointer(texcoord_position, 2,/* size : U+V => 2*/GL_FLOAT, GL_FALSE, 0, (void*)0);

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
	if (swap_the_Buffers){
		swapBuffers();
	}

};
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
void GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE>::swapBuffers(){

	(swap_buffers_func_class->*swapBuffersFunc)();

}
#endif

