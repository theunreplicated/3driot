#include "GLProgram.h"
#include "OpenGLImport.h"
using namespace OGL;
GL_Program::GL_Program(){
	m_program_id = glCreateProgram();
	

}
void GL_Program::assign_shaders(ShaderSource_Shader_IDs shader_ids){
	glAttachShader(m_program_id, shader_ids.vertex_id);
	glAttachShader(m_program_id, shader_ids.fragment_id);
	glLinkProgram(m_program_id);

	//check
	GLint Result = GL_FALSE;
	int InfoLogLength;

	glGetProgramiv(m_program_id, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	char*ProgramErrorMessage = new char[max(InfoLogLength, int(1))];
	glGetProgramInfoLog(m_program_id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	//fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
	OutputDebugString(&ProgramErrorMessage[0]);
	delete[] ProgramErrorMessage;


	glDeleteShader(shader_ids.vertex_id);
	glDeleteShader(shader_ids.fragment_id);

}
GL_Program::~GL_Program(){

	glDeleteProgram(m_program_id);

}