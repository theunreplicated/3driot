#include "OpenGLContext.h"
OpenGLContext::OpenGLContext(HWND window, SysUtils_Load_Library* dll_opengl){


	
	//zurückgreifen:http://www.opengl.org/wiki/Creating_an_OpenGL_Context_(WGL)
	//http://www.cs.rit.edu/~ncs/Courses/570/UserGuide/OpenGLonWin-11.html
	// get the device context (DC)
	m_device_context = ::GetDC(window);

	

	// create and enable the render context (RC)
	sd_wgl_getProcAddress gl_layer_getProcAddress = dll_opengl->import<sd_wgl_getProcAddress>("wglGetProcAddress");
	//auto wgl_mkCurrentProc = sd_wgl_getProcAddress("wglMakeCurrent");
	//if (wgl_mkCurrentProc){
	//sd_wgl_MakeCurrentProc gl_layer_MakeCurrent = reinterpret_cast<sd_wgl_MakeCurrentProc>(GetProcAddress(opengl_lib, "wglMakeCurrent"));

	gl_layer_MakeCurrent = dll_opengl->import<sd_wgl_MakeCurrentProc>("wglMakeCurrent");
	//über wglgetprocaddress gehts net
	//}
	//aus Faulheit keine Checks bei den andern,sonst müsste die wgl kaputt sein oder dieses Programm uralt
	gl_layer_CreateContext = dll_opengl->import<sd_wgl_CreateContextProc>("wglCreateContext");
	gl_layer_DeleteContext = dll_opengl->import<sd_wgl_DeleteContextProc>("wglDeleteContext");
	Enable_to_DeviceContext(m_device_context);
	//*hRC = wglCreateContext(*hDC);
	//wglMakeCurrent(*hDC, *hRC);
	//HDC hDC; HGLRC hRC;
	//EnableOpenGL(window,&device_context,&hRC);

}
void OpenGLContext::SwapBuffers(){

	::SwapBuffers(m_device_context);
}
void OpenGLContext::Enable_to_DeviceContext(HDC device_context){
	PIXELFORMATDESCRIPTOR pfd;
	int format;
	// set the pixel format for the DC
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	format = ChoosePixelFormat(device_context, &pfd);
	SetPixelFormat(device_context, format, &pfd);
	hRC = gl_layer_CreateContext(device_context);
	gl_layer_MakeCurrent(device_context, hRC);
	m_device_context = device_context;
}
/*
 void OpenGLContext::EnableOpenGL(HWND hWnd, HDC * hDC, HGLRC * hRC)
 {
 PIXELFORMATDESCRIPTOR pfd;
 int format;
 //zurückgreifen:http://www.opengl.org/wiki/Creating_an_OpenGL_Context_(WGL)
 //http://www.cs.rit.edu/~ncs/Courses/570/UserGuide/OpenGLonWin-11.html
 // get the device context (DC)
 *hDC = GetDC(hWnd);

 // set the pixel format for the DC
 ZeroMemory(&pfd, sizeof(pfd));
 pfd.nSize = sizeof(pfd);
 pfd.nVersion = 1;
 pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
 pfd.iPixelType = PFD_TYPE_RGBA;
 pfd.cColorBits = 24;
 pfd.cDepthBits = 16;
 pfd.iLayerType = PFD_MAIN_PLANE;
 format = ChoosePixelFormat(*hDC, &pfd);
 SetPixelFormat(*hDC, format, &pfd);

 // create and enable the render context (RC)
 *hRC = gl_layer_CreateContext(*hDC);
 gl_layer_MakeCurrent(*hDC, *hRC);

 //*hRC = wglCreateContext(*hDC);
 //wglMakeCurrent(*hDC, *hRC);


 }*/
OpenGLContext::~OpenGLContext(){
	gl_layer_MakeCurrent(NULL, NULL);
	gl_layer_DeleteContext(hRC);
	//wglMakeCurrent(NULL, NULL);
	//wglDeleteContext(hRC);
	::ReleaseDC(window_handle, m_device_context);

}