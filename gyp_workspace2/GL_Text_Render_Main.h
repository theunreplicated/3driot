#ifndef INC_GL_Text_Render_MAIN_H
#define INC_GL_Text_Render_MAIN_H//pragma once führz zu fehlern bei templates,also net soo verwenden
#include "../window2/GLProgram.h"
#include "../window2/OpenGL_Data_Types.h"
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>//natürlich orientiert an GLMAin.h
class GL_Text_Render_Main{
public:
	GL_Text_Render_Main(T_swapBuffersFuncType swapBuffersFunc, T_swapBuffers_class_reference *swapBuffersFuncClass, bool use_legacy_system_opengl);
	void set_current_program(GL_Program* program);
	void initGL(GL_Program*program_to_start_with);
	void render(bool swap_the_Buffers = true/*@TODO:hier entfernen,nur problem fals fvererbung,am besten wäre son n boost lb das unnötige argumente weglässt//ich bin studierter Linguist;-)kann das alles lesen und weiß was bedeutet*/);
private:
	GLuint vbo;
	T_swapBuffers_class_reference *m_swap_buffers_func_class;
	T_swapBuffersFuncType m_swapBuffersFunc;
	GL_Program *m_current_program;
	GLuint bindAttribLocation(const char* attrib_name);
	GLuint loc_position, loc_texture, loc_color;

};
#include "GL_Text_Render_Main.cpp"
#endif