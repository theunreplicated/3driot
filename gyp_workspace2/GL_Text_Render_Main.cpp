#ifndef INC_GL_Text_Render_MAIN_CPP
#define INC_GL_Text_Render_MAIN_CPP
#include "GL_Text_Render_Main.h"
#include "FreeTypeImplementation.h"
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>//natürlich orientiert an GLMAin.h
GL_Text_Render_Main<T_swapBuffersFuncType, T_swapBuffers_class_reference>::GL_Text_Render_Main(T_swapBuffersFuncType swapBuffersFunc, T_swapBuffers_class_reference *swapBuffersFuncClass, bool use_legacy_system_opengl){
	m_swapBuffersFunc = swapBuffersFunc;
	m_swap_buffers_func_class = swapBuffersFuncClass;

}

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>//natürlich orientiert an GLMAin.h
void GL_Text_Render_Main<T_swapBuffersFuncType, T_swapBuffers_class_reference>::set_current_program(GL_Program* program){
	m_current_program = program; glUseProgram(program->m_program_id);//@TODO:inheritance hier doen;-)
	loc_position = m_current_program->bindAttribLocation("vertexPosition_modelspace");
	loc_texture=glGetUniformLocation(m_current_program->m_program_id,"myTextureSampler");
	loc_color = glGetUniformLocation(m_current_program->m_program_id,"color");//kapselung ist schon was sehr gutes wie man hier sieht

}

template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GL_Text_Render_Main<T_swapBuffersFuncType, T_swapBuffers_class_reference>::initGL(GL_Program*program_to_start_with){
	set_current_program(program_to_start_with);
	//@TODO:
	glGenBuffers(1, &vbo);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference>
void GL_Text_Render_Main<T_swapBuffersFuncType, T_swapBuffers_class_reference>::render(bool swap_the_Buffers){

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);///weiß(ich net obs weiß ist ;-))
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepthf(1.0);
	//@TODO://quelle:wikibooks,geht aber net
	GLfloat black[4] = { 0, 0, 0, 1 };
	GLfloat red[4] = { 1, 0, 0, 1 };
	GLfloat transparent_green[4] = { 0, 1, 0, 0.5 };
	glUniform4fv(loc_color, 1, red);
	GLuint tex;

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(loc_texture, 0);

	/* We require 1 byte alignment when uploading texture data */
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/* Clamping to edges is important to prevent artifacts when scaling */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	/* Linear filtering usually looks best for text */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	/* Set up the VBO for our vertex data */
	glEnableVertexAttribArray(loc_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(loc_position, 4, GL_FLOAT, GL_FALSE, 0, 0);
FreeType_Implementation*ft = new FreeType_Implementation();
	FreeType_Face*fc = new FreeType_Face(ft, "C:\\Windows\\Fonts\\arial.ttf", 55);
	const char*text = "Hallo";
	const char*p;
	FT_GlyphSlot g=nullptr;
	
	for (p = text; *p; p++) {
		g = fc->load_char(*p);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			g->bitmap.width,
			g->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			g->bitmap.buffer
			);
		auto sx = 500, sy = 500; auto y=0, x = 0;
		float x2 = x + g->bitmap_left * sx;
		float y2 = -y - g->bitmap_top * sy;
		float w = g->bitmap.width * sx;
		float h = g->bitmap.rows * sy;

		GLfloat box[4][4] = {
			{ x2, -y2, 0, 0 },
			{ x2 + w, -y2, 1, 0 },
			{ x2, -y2 - h, 0, 1 },
			{ x2 + w, -y2 - h, 1, 1 },
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (g->advance.x >> 6) * sx;
		y += (g->advance.y >> 6) * sy;
	}



	//am schluss ,der letzte Schuss
	if (swap_the_Buffers){
		(m_swap_buffers_func_class->*m_swapBuffersFunc)(); };
}
#endif