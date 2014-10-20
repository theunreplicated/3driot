#pragma once
#include "ShaderSource.h"
class GL_Program{
	
public:
	unsigned int m_program_id;
	unsigned int attrib_location_counter = 0;
	GL_Program();
	void assign_shaders(ShaderSource_Shader_IDs shader_ids);
	~GL_Program();
};