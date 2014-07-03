#ifndef OpenGL_Context_H
#define OpenGL_Context_H
#include <Windows.h>
#include "SysUtils_Load_Library.h"
typedef HGLRC(__stdcall*sd_wgl_CreateContextProc)(HDC);
typedef bool(__stdcall*sd_wgl_MakeCurrentProc)(HDC, HGLRC);
typedef bool(__stdcall*sd_wgl_DeleteContextProc)(HGLRC);
typedef PROC(__stdcall*sd_wgl_getProcAddress)(LPCSTR);

class OpenGLContext{
private:
	sd_wgl_MakeCurrentProc gl_layer_MakeCurrent;
	sd_wgl_DeleteContextProc gl_layer_DeleteContext;
	sd_wgl_CreateContextProc gl_layer_CreateContext;
public:

	OpenGLContext(HWND window, SysUtils_Load_Library * dll_opengl);
	~OpenGLContext();
	void OpenGLContext::SwapBuffers();
private:
	//	void EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC);
	HGLRC hRC;
	HWND window_handle;
	HDC device_context;

};
typedef void(OpenGLContext::*swapBuffersFunc)(void);

#endif