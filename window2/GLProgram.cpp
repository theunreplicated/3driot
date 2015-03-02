#include "GLProgram.h"

using namespace OGL;
GL_Program::GL_Program(){
	m_program_id = glCreateProgram();
	

}
GLuint GL_Program::bindAttribLocation(const char* attrib_name){
	//https://www.opengl.org/discussion_boards/showthread.php/171837-glBindAttribLocation-after-glLinkProgram
	//muss vor glLinkProgram(damit Shader linken)aufgerufen werden,damit vor initGL
	glBindAttribLocation(m_program_id, attrib_location_counter, attrib_name);
	attrib_location_counter++;
	return (attrib_location_counter - 1);
}
void GL_Program::assign_shaders(ShaderSource_Shader_IDs shader_ids){
	glAttachShader(m_program_id, shader_ids.vertex_id);
	glAttachShader(m_program_id, shader_ids.fragment_id);
	glLinkProgram(m_program_id);

	//check
	GLint Result = GL_FALSE;
	int InfoLogLength;
	//nur noch sehr wenig vom orogonal-code von opengl-programming;boah stell vor ich find die schreibfehler auf einmal lustig.orogonal.hihihi.hahha.wie lustig..hohohohoho
	glGetProgramiv(m_program_id, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_program_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	char*ProgramErrorMessage = new char[max(InfoLogLength, int(1))];
	glGetProgramInfoLog(m_program_id, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	
	OutputDebugString(&ProgramErrorMessage[0]);
	delete[] ProgramErrorMessage;


	glDeleteShader(shader_ids.vertex_id);
	glDeleteShader(shader_ids.fragment_id);

}
GL_Program::~GL_Program(){

	glDeleteProgram(m_program_id);

}