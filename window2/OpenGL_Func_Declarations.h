#ifndef INC_OPENGL_FUNC_DECALRATIONS_H
#define INC_OPENGL_FUNC_DECALRATIONS_H
#include "ext\skia\GrGLFunctions.h"
#include "OpenGL_Data_Types.h"
#include <Windows.h>
//die Makros hier können nur in dieser Klasse verwendet werden

#define IMPORT_GL_DECLARE(fname) GrGL ## fname ## Proc gl##fname




/*
namespace OGL{
	GLenum GL_VERTEX_SHADER = 0x8B31;
	GLenum GL_ARRAY_BUFFER = 0x8892;//TODO merge zu einem
	GLenum GL_STATIC_DRAW = 0x88E4;
	GLenum GL_ELEMENT_ARRAY_BUFFER = 0x8893;

	GLenum GL_FRAGMENT_SHADER = 0x8B30;//https://chromium.googlesource.com/angle/angle/+/master/include/GLES2/gl2.h
	GLenum  GL_LINK_STATUS = 0x8B82;
	GLenum GL_UNSIGNED_INT = 0x1405;
	GLenum GL_UNSIGNED_SHORT = 0x1403;
	GLenum GL_FALSE = 0;
	GLenum GL_TRUE = 0;
	GLenum GL_FLOAT = 0x1406;
	GLenum GL_TRIANGLES = 0x0004;
	GLenum GL_VERSION = 0x1F02;
	
}
int dc;
*/
#endif