#ifndef INC_Open_GL_IMPORT//_H
#define INC_Open_GL_IMPORT//_H
#include "ext\skia\GrGLFunctions.h"
#include <Windows.h>
#include "OpenGL_Data_Types.h"
#include <iostream>
//die Makros hier können nur in dieser Klasse verwendet werden
#define IMPORT_GL(name,proc) name=reinterpret_cast<proc>(this_scope_gl_import(#name,import,importGLES11withExceptions))
//#define IMPORT_GL_FUNC(fname) gl ## fname=reinterpret_cast<GrGL ## fname ## Proc>(import("gl" #fname))
#define IMPORT_GL_FUNC(fname)  IMPORT_GL(gl ## fname,GrGL ## fname ## Proc)
#define IMPORT_GL_DECLARE(fname) GrGL ## fname ## Proc gl##fname

template <typename T_func_name, typename T_wglgetprocadr, typename T_getprocaddr>
PROC __stdcall this_scope_gl_import(T_func_name name, T_wglgetprocadr wglgetadr, T_getprocaddr globalgetadr){
	PROC __stdcall wglres = wglgetadr(name);
	return (wglres ? wglres : (globalgetadr(name) ? globalgetadr(name) : throw std::runtime_error("cannot load dingens")));

};
namespace OGL{

	//GrGLCreateShaderProc __stdcall glCreateShader;
	IMPORT_GL_DECLARE(CreateShader);
	//GrGLCreateShaderProc glCreateShader;
	IMPORT_GL_DECLARE(ShaderSource);
	IMPORT_GL_DECLARE(CompileShader);
	IMPORT_GL_DECLARE(GetShaderiv);
	IMPORT_GL_DECLARE(GetShaderInfoLog);
	IMPORT_GL_DECLARE(DeleteShader);
	IMPORT_GL_DECLARE(AttachShader);
	IMPORT_GL_DECLARE(ClearColor);
	IMPORT_GL_DECLARE(Clear);
	IMPORT_GL_DECLARE(GetString);
	//draw calls
	IMPORT_GL_DECLARE(DrawArrays);
	IMPORT_GL_DECLARE(DrawElements);


	//program
	IMPORT_GL_DECLARE(CreateProgram);
	IMPORT_GL_DECLARE(DeleteProgram);
	IMPORT_GL_DECLARE(LinkProgram);
	IMPORT_GL_DECLARE(GetProgramiv);
	IMPORT_GL_DECLARE(GetProgramInfoLog);
	IMPORT_GL_DECLARE(UseProgram);
	
	IMPORT_GL_DECLARE(BindAttribLocation);
	IMPORT_GL_DECLARE(GetUniformLocation);
	//struct Vertex_Attrib_Pointers{
	IMPORT_GL_DECLARE(VertexAttribPointer);
	IMPORT_GL_DECLARE(EnableVertexAttribArray);
	IMPORT_GL_DECLARE(DisableVertexAttribArray);

	//};	
	//struct Uniforms{
	IMPORT_GL_DECLARE(UniformMatrix4fv);

	//IMPORT_GL_DECLARE(GenVertexArrays);
	//IMPORT_GL_DECLARE(BindVertexArray);

	
	IMPORT_GL_DECLARE(GenBuffers);
	IMPORT_GL_DECLARE(BindBuffer);
	IMPORT_GL_DECLARE(BufferData);

	IMPORT_GL_DECLARE(Viewport);
	IMPORT_GL_DECLARE(Scissor);
	IMPORT_GL_DECLARE(Enable);

	IMPORT_GL_DECLARE(PixelStorei);
	IMPORT_GL_DECLARE(GenTextures);
	IMPORT_GL_DECLARE(BindTexture);
	IMPORT_GL_DECLARE(TexImage2D);
	IMPORT_GL_DECLARE(TexParameteri);
	IMPORT_GL_DECLARE(ActiveTexture);
	IMPORT_GL_DECLARE(Uniform1i);
	//typedef SD_GL_DepthFuncProc
	typedef void(GR_GL_FUNCTION_TYPE*SD_GL_DepthFuncProc)(GrGLenum func);//@TODOL:brauch man vllt. gar net,da wohl default auf GL_LESS,daher wohl auch nicht im skia defs'0>chromium drin
	SD_GL_DepthFuncProc glDepthFunc;
	typedef void(GR_GL_FUNCTION_TYPE*SD_GL_ClearDepthfProc)(GLclampf depth);
	SD_GL_ClearDepthfProc glClearDepthf;
	typedef void(GR_GL_FUNCTION_TYPE*SD_GL_DepthRangefProc)(GLclampf zNear, GLclampf zFar);
	SD_GL_DepthRangefProc glDepthRangef;
	IMPORT_GL_DECLARE(DepthMask);
	IMPORT_GL_DECLARE(ReadPixels);
	IMPORT_GL_DECLARE(GetError);
	IMPORT_GL_DECLARE(BindFramebuffer);
	IMPORT_GL_DECLARE(GenFramebuffers);
	IMPORT_GL_DECLARE(GenRenderbuffers);
	IMPORT_GL_DECLARE(BindRenderbuffer);
	IMPORT_GL_DECLARE(RenderbufferStorage);
	IMPORT_GL_DECLARE(FramebufferRenderbuffer);
	IMPORT_GL_DECLARE(CheckFramebufferStatus);
}

namespace OGL{
	GLenum GL_VERTEX_SHADER = 0x8B31;
	GLenum GL_ARRAY_BUFFER = 0x8892;
	GLenum GL_STATIC_DRAW = 0x88E4;
	GLenum GL_ELEMENT_ARRAY_BUFFER = 0x8893;
	
	GLenum GL_FRAGMENT_SHADER = 0x8B30;//https://chromium.googlesource.com/angle/angle/+/master/include/GLES2/gl2.h
	GLenum  GL_LINK_STATUS = 0x8B82;
	GLenum GL_UNSIGNED_INT = 0x1405;
	GLenum GL_UNSIGNED_SHORT = 0x1403;
	GLenum GL_FALSE = 0;
	GLenum GL_TRUE = 1;
	GLenum GL_FLOAT = 0x1406;
	const GLenum GL_TRIANGLES = 0x0004;//TODO merge zu einem
	GLenum GL_VERSION = 0x1F02;
	GLenum GL_SCISSOR_TEST = 0x0C11;
	GLenum GL_UNPACK_ALIGNMENT=0x0CF5;
	GLenum GL_DEPTH_TEST=0x0B71;
	GLenum GL_TEXTURE_2D=0x0DE1;
	GLenum GL_CULL_FACE=0x0B44;
	GLenum GL_RGBA= 0x1908;
	GLenum GL_UNSIGNED_BYTE=0x1401;
	GLenum GL_NEAREST=0x2600;
	GLenum GL_TEXTURE_MIN_FILTER=0x2801;
	GLenum GL_TEXTURE_MAG_FILTER=0x2800;
	GLenum GL_TEXTURE0=0x84C0;
	GLenum GL_RGB=0x1907;
	GLenum GL_LESS=0x0201;
	GLenum GL_DEPTH_BUFFER_BIT=0x00000100;
	GLenum GL_COLOR_BUFFER_BIT=0x00004000;
	GLenum GL_BGR = 0x80E0;
	GLenum GL_BGRA=0x80E1;
	GLenum GL_LEQUAL=0x0203;
	GLenum GL_DEPTH_COMPONENT=0x1902;
	GLenum GL_DEPTH_COMPONENT16 = 0x81A5;
	GLenum GL_BYTE =0x1400;
	GLenum GL_RED_BITS=0x0D52;
	GLenum GL_GREEN_BITS=0x0D53;
	GLenum GL_BLUE_BITS=0x0D54;
	GLenum GL_STENCIL_INDEX8=0x8D48;
	GLenum GL_RGBA4=0x8056;
	GLenum GL_RED = 0x1903;//nicht in gles 2.0

	//errors
	const GLenum GL_NO_ERROR = 0;
	const GLenum GL_INVALID_ENUM=0x0500;
	const GLenum GL_INVALID_VALUE=0x0501;
	const GLenum GL_INVALID_OPERATION=0x0502;
	const GLenum GL_OUT_OF_MEMORY = 0x0505;

	const GLenum GL_FRAMEBUFFER = 0x8D40;
	const GLenum GL_RENDERBUFFER=0x8D41;
	const GLenum GL_COLOR_ATTACHMENT0=0x8CE0;
	const GLenum GL_DEPTH_ATTACHMENT=0x8D00;
	const GLenum GL_RGBA8=0x8058;//@TODO:code damit entferene,da vermutlich nicht teil von gles 2.0
	const GLenum GL_FRAMEBUFFER_COMPLETE = 0x8CD5;

}
class OpenGLImport{

public:
	template <typename T_ogl_import_func, typename T_getprocaddress_ogl_so>
	OpenGLImport(T_ogl_import_func import, T_getprocaddress_ogl_so importGLES11withExceptions);
};

template <typename T_ogl_import_func, typename T_getprocaddress_ogl_so>
OpenGLImport::OpenGLImport(T_ogl_import_func import, T_getprocaddress_ogl_so importGLES11withExceptions){
	using namespace OGL;
	//glCreateShader = reinterpret_cast<GrGLCreateShaderProc>(import("glCreateShader"));
	//IMPORT_GL(glCreateShader,GrGLCreateShaderProc);

	//
	/*IMPORT_GL(glShaderSource, GrGLShaderSourceProc);
	IMPORT_GL(glCompileShader, GrGLCompileShaderProc);
	IMPORT_GL(glGetShaderiv, GrGLGetShaderivProc);
	IMPORT_GL(glGetShaderInfoLog, GrGLGetShaderInfoLogProc);
	IMPORT_GL(glDeleteShader, GrGLDeleteShaderProc);
	//shader jetzt wieder-obwogl in funktion
	IMPORT_GL(glAttachShader, GrGLAttachShaderProc);*/

	IMPORT_GL_FUNC(CreateShader);
	IMPORT_GL_FUNC(ShaderSource);
	IMPORT_GL_FUNC(CompileShader);
	IMPORT_GL_FUNC(GetShaderiv);
	IMPORT_GL_FUNC(GetShaderInfoLog);
	IMPORT_GL_FUNC(DeleteShader);
	IMPORT_GL_FUNC(AttachShader);
	IMPORT_GL_FUNC(ClearColor);
	IMPORT_GL_FUNC(Clear);
	IMPORT_GL_FUNC(GetString);//glValidate ist wohl veraltet

	IMPORT_GL_FUNC(DrawArrays);
	IMPORT_GL_FUNC(DrawElements);

	IMPORT_GL_FUNC(CreateProgram);
	IMPORT_GL_FUNC(DeleteProgram);
	IMPORT_GL_FUNC(LinkProgram);
	IMPORT_GL_FUNC(GetProgramiv);
	IMPORT_GL_FUNC(GetProgramInfoLog);
	IMPORT_GL_FUNC(UseProgram);

	IMPORT_GL_FUNC(BindAttribLocation);//muss vor dem Linken aufgerufen werden http://stackoverflow.com/questions/12550570/some-names-for-glbindattriblocation-dont-work-objective-c-issue
	IMPORT_GL_FUNC(GetUniformLocation);

	IMPORT_GL_FUNC(VertexAttribPointer);
	IMPORT_GL_FUNC(EnableVertexAttribArray);
	IMPORT_GL_FUNC(DisableVertexAttribArray);

	IMPORT_GL_FUNC(UniformMatrix4fv);

	//IMPORT_GL_FUNC(GenVertexArrays);
	//IMPORT_GL_FUNC(BindVertexArray);

	IMPORT_GL_FUNC(GenBuffers);
	IMPORT_GL_FUNC(BindBuffer);
	IMPORT_GL_FUNC(BufferData);

	IMPORT_GL_FUNC(Viewport);
	IMPORT_GL_FUNC(Scissor);
	IMPORT_GL_FUNC(Enable);

	IMPORT_GL_FUNC(PixelStorei);
	IMPORT_GL_FUNC(GenTextures);
	IMPORT_GL_FUNC(BindTexture);
	IMPORT_GL_FUNC(TexImage2D);
	IMPORT_GL_FUNC(TexParameteri);
	IMPORT_GL_FUNC(ActiveTexture);
	IMPORT_GL_FUNC(Uniform1i);

	IMPORT_GL(glDepthFunc, SD_GL_DepthFuncProc);
	IMPORT_GL(glClearDepthf, SD_GL_ClearDepthfProc);
	IMPORT_GL(glDepthRangef, SD_GL_DepthRangefProc);
	IMPORT_GL_FUNC(DepthMask);
	IMPORT_GL_FUNC(ReadPixels);
	IMPORT_GL_FUNC(GetError);

	IMPORT_GL_FUNC(BindFramebuffer);
	IMPORT_GL_FUNC(GenFramebuffers);
	IMPORT_GL_FUNC(GenRenderbuffers);
	IMPORT_GL_FUNC(BindRenderbuffer);
	IMPORT_GL_FUNC(RenderbufferStorage);
	IMPORT_GL_FUNC(FramebufferRenderbuffer);
	IMPORT_GL_FUNC(CheckFramebufferStatus);
	//@TODO:in module machen,dann falss import fail->einzelen module nicht verfügbar
	//if (import("glDrawElements")){ OutputDebugString("----"); }
	//else{
	//OutputDebugString("!!!");
	//OutputDebugString(GetLastError()); 
	//}
	//glClearColor5 = reinterpret_cast<GrGLClearColorProc>(import("glClearColor"));
	//Hinweis=einige 
}
#endif