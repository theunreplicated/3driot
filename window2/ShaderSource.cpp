#include "ShaderSource.h"
#include "OpenGLImport.h"
#include "../window2/Resource_Loading.h"
#include "resource.h"
using namespace OGL;//schlechtes API_design hier ,immwer und wieder ,das schlechte API_Design verfolgt mich
unsigned int Shader_Source::compileshader(const int& shader_type/*@TODO:glenum draus machen*/,const ShaderSource_ShaderLocationDescription& shader_info){
	unsigned int m_shader_id = glCreateShader(shader_type);
	char const * VertexSourcePointer = Resource::CommonLoad(shader_info.name, shader_info.type);
	glShaderSource(m_shader_id, 1, &VertexSourcePointer, NULL);
	glCompileShader(m_shader_id);

	//check ob o.k.
	GLint Result = GL_FALSE;//so was könnte man öfters nutzen,vorteil von asm,da nur wenige Variablne? im Blick
	int InfoLogLength;
	glGetShaderiv(m_shader_id, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(m_shader_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	char* ShaderErrorMessage = new char[InfoLogLength];
	glGetShaderInfoLog(m_shader_id, InfoLogLength, NULL, &ShaderErrorMessage[0]);
	OutputDebugString(&ShaderErrorMessage[0]);
	delete[] ShaderErrorMessage;

		return m_shader_id;
}
Shader_Source::Shader_Source(ShaderSource_ShaderLocationDescription vertex, ShaderSource_ShaderLocationDescription shader){
	m_vertex = vertex; m_fragment = shader; 
}
ShaderSource_Shader_IDs Shader_Source::setup_for_usage_by_program(){
	shader_ids = { compileshader(GL_VERTEX_SHADER, m_vertex), compileshader(GL_FRAGMENT_SHADER, m_fragment) };
	
	return shader_ids;
}

