#ifndef INC_OPENGL_FUNCTIONS_H
#define INC_OPENGL_FUNCTIONS_H
#include "..\window2\ext\skia\GrGLFunctions.h"
#include "../window2/OpenGL_Data_Types.h"
//die Makros hier können nur in dieser Klasse verwendet werden
#define IMPORT_GL(name,proc) name=reinterpret_cast<proc>(this_scope_gl_import(#name,import,importGLES11withExceptions))
//#define IMPORT_GL_FUNC(fname) gl ## fname=reinterpret_cast<GrGL ## fname ## Proc>(import("gl" #fname))
#define IMPORT_GL_FUNC(fname)  IMPORT_GL(gl ## fname,GrGL ## fname ## Proc)
#define IMPORT_GL_DECLARE(fname) extern GrGL ## fname ## Proc gl##fname
#define IMPORT_GL_DECLARE_NORMAL(fname) GrGL ## fname ## Proc gl##fname
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
	IMPORT_GL_DECLARE(Uniform4fv);
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
	extern SD_GL_DepthFuncProc glDepthFunc;
	typedef void(GR_GL_FUNCTION_TYPE*SD_GL_ClearDepthfProc)(GLclampf depth);
	extern SD_GL_ClearDepthfProc glClearDepthf;
	typedef void(GR_GL_FUNCTION_TYPE*SD_GL_DepthRangefProc)(GLclampf zNear, GLclampf zFar);
	extern SD_GL_DepthRangefProc glDepthRangef;
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

	IMPORT_GL_DECLARE(BlendFunc);
}

namespace OGL{
	extern const GLenum GL_VERTEX_SHADER;
	extern const GLenum GL_ARRAY_BUFFER;
	extern const GLenum GL_STATIC_DRAW;
	extern const GLenum GL_DYNAMIC_DRAW;
	extern const GLenum GL_ELEMENT_ARRAY_BUFFER;

	extern const GLenum GL_FRAGMENT_SHADER;//https://chromium.googlesource.com/angle/angle/+/master/include/GLES2/gl2.h
	extern const GLenum  GL_LINK_STATUS;
	extern const GLenum GL_UNSIGNED_INT;
	extern const GLenum GL_UNSIGNED_SHORT;
	extern const GLenum GL_FALSE;
	extern const GLenum GL_TRUE;
	extern const  GLenum GL_FLOAT;
	extern const GLenum GL_TRIANGLES;//TODO merge zu einem
	extern const GLenum GL_TRIANGLE_STRIP;
	extern const GLenum GL_VERSION;
	extern const GLenum GL_SCISSOR_TEST;
	extern const GLenum GL_UNPACK_ALIGNMENT;
	extern const GLenum GL_DEPTH_TEST;
	extern const GLenum GL_TEXTURE_2D;
	extern const GLenum GL_CULL_FACE;
	extern const GLenum GL_RGBA;
	extern const GLenum GL_UNSIGNED_BYTE;
	extern const GLenum GL_NEAREST;
	extern const GLenum GL_TEXTURE_MIN_FILTER;
	extern const GLenum GL_TEXTURE_MAG_FILTER;
	extern const GLenum GL_TEXTURE_WRAP_S;
	extern const GLenum GL_TEXTURE_WRAP_T;
	extern const GLenum GL_CLAMP_TO_EDGE;
	extern const GLenum GL_LINEAR;
	extern const GLenum GL_TEXTURE0;
	extern const GLenum GL_RGB;
	extern const GLenum GL_LESS;
	extern const GLenum GL_DEPTH_BUFFER_BIT;
	extern const GLenum GL_COLOR_BUFFER_BIT;
	extern const GLenum GL_BGR;
	extern const GLenum GL_BGRA;
	extern const GLenum GL_LEQUAL;
	extern const GLenum GL_DEPTH_COMPONENT;
	extern const GLenum GL_DEPTH_COMPONENT16;
	extern const GLenum GL_BYTE;
	extern const GLenum GL_RED_BITS;
	extern const GLenum GL_GREEN_BITS;
	extern const GLenum GL_BLUE_BITS;
	extern const GLenum GL_STENCIL_INDEX8;
	extern const GLenum GL_RGBA4;
	extern const GLenum GL_RED;//nicht in gles 2.0

	//errors
	extern const GLenum GL_NO_ERROR;
	extern const GLenum GL_INVALID_ENUM;
	extern const GLenum GL_INVALID_VALUE;
	extern const GLenum GL_INVALID_OPERATION;
	extern const GLenum GL_OUT_OF_MEMORY;

	extern const GLenum GL_FRAMEBUFFER;
	extern const GLenum GL_RENDERBUFFER;
	extern const GLenum GL_COLOR_ATTACHMENT0;
	extern const GLenum GL_DEPTH_ATTACHMENT;
	extern const GLenum GL_RGBA8;//@TODO:code damit entferene,da vermutlich nicht teil von gles 2.0
	extern const GLenum GL_FRAMEBUFFER_COMPLETE;
	extern const GLenum GL_COMPILE_STATUS;
	extern const GLenum GL_INFO_LOG_LENGTH;
	extern const GLenum GL_BLEND;
	extern const GLenum GL_SRC_ALPHA;
	extern const GLenum GL_ONE_MINUS_SRC_ALPHA;
}
#endif