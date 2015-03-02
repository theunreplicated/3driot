#pragma once
#include "ShaderSource.h"
#include "OpenGLImport.h"
class GL_Program{
	
public:
	unsigned int m_program_id;
	unsigned int attrib_location_counter = 0;
	GL_Program();
	GLuint bindAttribLocation(const char* attrib_name);
	void assign_shaders(ShaderSource_Shader_IDs shader_ids);
	~GL_Program();
};