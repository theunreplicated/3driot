#include "OpenGLFunctions.h"

namespace OGL{

	//GrGLCreateShaderProc __stdcall glCreateShader;
	IMPORT_GL_DECLARE_NORMAL(CreateShader);
	//GrGLCreateShaderProc glCreateShader;
	IMPORT_GL_DECLARE_NORMAL(ShaderSource);
	IMPORT_GL_DECLARE_NORMAL(CompileShader);
	IMPORT_GL_DECLARE_NORMAL(GetShaderiv);
	IMPORT_GL_DECLARE_NORMAL(GetShaderInfoLog);
	IMPORT_GL_DECLARE_NORMAL(DeleteShader);
	IMPORT_GL_DECLARE_NORMAL(AttachShader);
	IMPORT_GL_DECLARE_NORMAL(ClearColor);
	IMPORT_GL_DECLARE_NORMAL(Clear);
	IMPORT_GL_DECLARE_NORMAL(GetString);
	//draw calls
	IMPORT_GL_DECLARE_NORMAL(DrawArrays);
	IMPORT_GL_DECLARE_NORMAL(DrawElements);


	//program
	IMPORT_GL_DECLARE_NORMAL(CreateProgram);
	IMPORT_GL_DECLARE_NORMAL(DeleteProgram);
	IMPORT_GL_DECLARE_NORMAL(LinkProgram);
	IMPORT_GL_DECLARE_NORMAL(GetProgramiv);
	IMPORT_GL_DECLARE_NORMAL(GetProgramInfoLog);
	IMPORT_GL_DECLARE_NORMAL(UseProgram);

	IMPORT_GL_DECLARE_NORMAL(BindAttribLocation);
	IMPORT_GL_DECLARE_NORMAL(GetUniformLocation);
	//struct Vertex_Attrib_Pointers{
	IMPORT_GL_DECLARE_NORMAL(VertexAttribPointer);
	IMPORT_GL_DECLARE_NORMAL(EnableVertexAttribArray);
	IMPORT_GL_DECLARE_NORMAL(DisableVertexAttribArray);

	//};	
	//struct Uniforms{
	IMPORT_GL_DECLARE_NORMAL(UniformMatrix4fv);

	//IMPORT_GL_DECLARE_NORMAL(GenVertexArrays);
	//IMPORT_GL_DECLARE_NORMAL(BindVertexArray);


	IMPORT_GL_DECLARE_NORMAL(GenBuffers);
	IMPORT_GL_DECLARE_NORMAL(BindBuffer);
	IMPORT_GL_DECLARE_NORMAL(BufferData);

	IMPORT_GL_DECLARE_NORMAL(Viewport);
	IMPORT_GL_DECLARE_NORMAL(Scissor);
	IMPORT_GL_DECLARE_NORMAL(Enable);

	IMPORT_GL_DECLARE_NORMAL(PixelStorei);
	IMPORT_GL_DECLARE_NORMAL(GenTextures);
	IMPORT_GL_DECLARE_NORMAL(BindTexture);
	IMPORT_GL_DECLARE_NORMAL(TexImage2D);
	IMPORT_GL_DECLARE_NORMAL(TexParameteri);
	IMPORT_GL_DECLARE_NORMAL(ActiveTexture);
	IMPORT_GL_DECLARE_NORMAL(Uniform1i);
	//typedef SD_GL_DepthFuncProc
	typedef void(GR_GL_FUNCTION_TYPE*SD_GL_DepthFuncProc)(GrGLenum func);//@TODOL:brauch man vllt. gar net,da wohl default auf GL_LESS,daher wohl auch nicht im skia defs'0>chromium drin
	SD_GL_DepthFuncProc glDepthFunc;
	typedef void(GR_GL_FUNCTION_TYPE*SD_GL_ClearDepthfProc)(GLclampf depth);
	SD_GL_ClearDepthfProc glClearDepthf;
	typedef void(GR_GL_FUNCTION_TYPE*SD_GL_DepthRangefProc)(GLclampf zNear, GLclampf zFar);
	SD_GL_DepthRangefProc glDepthRangef;
	IMPORT_GL_DECLARE_NORMAL(DepthMask);
	IMPORT_GL_DECLARE_NORMAL(ReadPixels);
	IMPORT_GL_DECLARE_NORMAL(GetError);
	IMPORT_GL_DECLARE_NORMAL(BindFramebuffer);
	IMPORT_GL_DECLARE_NORMAL(GenFramebuffers);
	IMPORT_GL_DECLARE_NORMAL(GenRenderbuffers);
	IMPORT_GL_DECLARE_NORMAL(BindRenderbuffer);
	IMPORT_GL_DECLARE_NORMAL(RenderbufferStorage);
	IMPORT_GL_DECLARE_NORMAL(FramebufferRenderbuffer);
	IMPORT_GL_DECLARE_NORMAL(CheckFramebufferStatus);
}
namespace OGL{
	const GLenum GL_VERTEX_SHADER = 0x8B31;
	const GLenum GL_ARRAY_BUFFER = 0x8892;
	const GLenum GL_STATIC_DRAW = 0x88E4;
	const GLenum GL_ELEMENT_ARRAY_BUFFER = 0x8893;

	const GLenum GL_FRAGMENT_SHADER = 0x8B30;//https://chromium.googlesource.com/angle/angle/+/master/include/GLES2/gl2.h
	const GLenum  GL_LINK_STATUS = 0x8B82;
	const GLenum GL_UNSIGNED_INT = 0x1405;
	const GLenum GL_UNSIGNED_SHORT = 0x1403;
	const GLenum GL_FALSE = 0;
	const GLenum GL_TRUE = 1;
	const  GLenum GL_FLOAT = 0x1406;
	const GLenum GL_TRIANGLES = 0x0004;//TODO merge zu einem
	const GLenum GL_VERSION = 0x1F02;
	const GLenum GL_SCISSOR_TEST = 0x0C11;
	const GLenum GL_UNPACK_ALIGNMENT = 0x0CF5;
	const GLenum GL_DEPTH_TEST = 0x0B71;
	const GLenum GL_TEXTURE_2D = 0x0DE1;
	const GLenum GL_CULL_FACE = 0x0B44;
	const GLenum GL_RGBA = 0x1908;
	const GLenum GL_UNSIGNED_BYTE = 0x1401;
	const GLenum GL_NEAREST = 0x2600;
	const GLenum GL_TEXTURE_MIN_FILTER = 0x2801;
	const GLenum GL_TEXTURE_MAG_FILTER = 0x2800;
	const GLenum GL_TEXTURE0 = 0x84C0;
	const GLenum GL_RGB = 0x1907;
	const GLenum GL_LESS = 0x0201;
	const GLenum GL_DEPTH_BUFFER_BIT = 0x00000100;
	const GLenum GL_COLOR_BUFFER_BIT = 0x00004000;
	const GLenum GL_BGR = 0x80E0;
	const GLenum GL_BGRA = 0x80E1;
	const GLenum GL_LEQUAL = 0x0203;
	const GLenum GL_DEPTH_COMPONENT = 0x1902;
	const GLenum GL_DEPTH_COMPONENT16 = 0x81A5;
	const GLenum GL_BYTE = 0x1400;
	const GLenum GL_RED_BITS = 0x0D52;
	const GLenum GL_GREEN_BITS = 0x0D53;
	const GLenum GL_BLUE_BITS = 0x0D54;
	const GLenum GL_STENCIL_INDEX8 = 0x8D48;
	const GLenum GL_RGBA4 = 0x8056;
	const GLenum GL_RED = 0x1903;//nicht in gles 2.0

	//errors
	const GLenum GL_NO_ERROR = 0;
	const GLenum GL_INVALID_ENUM = 0x0500;
	const GLenum GL_INVALID_VALUE = 0x0501;
	const GLenum GL_INVALID_OPERATION = 0x0502;
	const GLenum GL_OUT_OF_MEMORY = 0x0505;

	const GLenum GL_FRAMEBUFFER = 0x8D40;
	const GLenum GL_RENDERBUFFER = 0x8D41;
	const GLenum GL_COLOR_ATTACHMENT0 = 0x8CE0;
	const GLenum GL_DEPTH_ATTACHMENT = 0x8D00;
	const GLenum GL_RGBA8 = 0x8058;//@TODO:code damit entferene,da vermutlich nicht teil von gles 2.0
	const GLenum GL_FRAMEBUFFER_COMPLETE = 0x8CD5;

}