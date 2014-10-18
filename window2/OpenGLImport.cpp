#ifndef INC_Open_GL_IMPORT_CPP
#define INC_Open_GL_IMPORT_CPP
#include "../window2/OpenGLImport.h"
#include "OpenGLFunctions.h"

template <typename T_func_name, typename T_wglgetprocadr, typename T_getprocaddr>
PROC __stdcall OpenGLImport::this_scope_gl_import(T_func_name name, T_wglgetprocadr wglgetadr, T_getprocaddr globalgetadr){
	PROC __stdcall wglres = wglgetadr(name);
	return (wglres ? wglres : (globalgetadr(name) ? globalgetadr(name) : throw std::runtime_error("cannot load dingens")));

};
template <typename T_ogl_import_func, typename T_getprocaddress_ogl_so>
OpenGLImport::OpenGLImport(T_ogl_import_func import, T_getprocaddress_ogl_so importGLES11withExceptions){
using namespace OGL;
//glCreateShader = reinterpret_cast<GrGLCreateShaderProc>(import("glCreateShader"));
//IMPORT_GL(glCreateShader,GrGLCreateShaderProc);

//
IMPORT_GL(glShaderSource, GrGLShaderSourceProc);
IMPORT_GL(glCompileShader, GrGLCompileShaderProc);
IMPORT_GL(glGetShaderiv, GrGLGetShaderivProc);
IMPORT_GL(glGetShaderInfoLog, GrGLGetShaderInfoLogProc);
IMPORT_GL(glDeleteShader, GrGLDeleteShaderProc);
//shader jetzt wieder-obwogl in funktion
IMPORT_GL(glAttachShader, GrGLAttachShaderProc);

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
