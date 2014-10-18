//#pragma once
#ifndef INC_APP_INITIALIZE_COMPONENTS_CPP
#define INC_APP_INITIALIZE_COMPONENTS_CPP
#include <Windows.h>
#include "GLMain.h"
#include "SysUtils_Load_Library.h"
#include "../Main/my_gfx_rect.h"
#include "standard_window.h"
#include "App_Intizialize_GL_DLL.h"
#include "OpenGLContext.h"
#ifdef USE_GLESV2
#include "egl_display_binding.cpp"
#endif
namespace Application{

	template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
	GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE> * setup_system_gl_opengl_layer(HWND native_window_handle, OpenGLContext*ctx){

#ifndef USE_GLESV2
		
		
		sd_wgl_getProcAddress gl_layer_getProcAddress = App_Inizialize_GL_DLL::dll_opengl->import<sd_wgl_getProcAddress>("wglGetProcAddress");

		//OpenGLContext*ctx = new OpenGLContext(native_window_handle, App_Inizialize_GL_DLL::dll_opengl);
		OpenGLImport imp(gl_layer_getProcAddress, App_Inizialize_GL_DLL::getProcAddresswglintf);
		return new GLMain<swapBuffersFunc, OpenGLContext, THREEDObject>(&OpenGLContext::SwapBuffers, ctx, true);

#else
		//@TODO:separate swapbuffers func ohne das mit den templates
		EGL_Display_Binding *g_display = new EGL_Display_Binding(::GetDC(native_window_handle), native_window_handle);
		g_display->createContext();

		std::string path22 = dir_path + "\\" + "libGLESv2.dll";//dynamisches dll laden jedoch langsamer als mit __declspec(dllimport)
		dll_opengl = new SysUtils_Load_Library(path22.c_str());//@TODO:verwendet standard dll,nicht die ,die ich will,also plus path
		OpenGLImport imp(getProcAddresswglintf, getProcAddresswglintf/*eigentlich egl*/);
		GLMain<EGLswapBuffersFunc, EGL_Display_Binding, THREEDObject> *glmain = new GLMain<EGLswapBuffersFunc, EGL_Display_Binding, THREEDObject>(&EGL_Display_Binding::swapBuffers, g_display, false);
#endif
	}
	template <typename T_swapBuffersFuncType, typename T_swapBuffers_class_reference, typename T_DRAW_STRUCTURE>
	void set_std_camera_projection_matrices(GLMain<T_swapBuffersFuncType, T_swapBuffers_class_reference, T_DRAW_STRUCTURE> *glmain, float current_resolution_w, float current_resolution_h){
		glm::mat4 matt2 = glm::perspective(45.0f, (current_resolution_w / current_resolution_h), 0.01f, 5000.0f);
		glm::mat4 model_mat = glm::mat4(1.0f);
		glm::mat4 camera_mat = glm::lookAt(
			glm::vec3(4, 3, 3),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
			);
		glmain->setCameraMatrix(camera_mat);
		glmain->setProjectionMatrix(matt2);
		glmain->setCameraTransformMatrix(model_mat);

	}
	LRESULT CALLBACK Basic_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
		switch (message)
		{

		case WM_CREATE:

			return 0;

		case WM_KEYDOWN:
			switch (wParam)
			{

			case VK_ESCAPE:

				PostQuitMessage(0);


			}
			return 0; break;
		case WM_CLOSE:
			PostQuitMessage(0); break;//Geht jetzt auch beim klick aufs x
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);

		}

	}
	struct window_info{
		bool maximized;
		LONG style, ex_style;
		RECT window_rect;

	};
	void fullscreen(Windows::standard_window*window){
		//http://stackoverflow.com/questions/2382464/win32-full-screen-and-hiding-taskbar
		//CHromium source
		HWND native_window_handle = window->window_handle;
#ifndef SCHLECHTER_STIL_KEIN_FULLSCREEN
		window_info saved_window_info_;
		saved_window_info_.maximized = !!::IsZoomed(native_window_handle);//ist es an dieser Stelle hier sicher nicht gezoomt
		if (saved_window_info_.maximized){//brauch man vllt. net immer
			::SendMessage(native_window_handle, WM_SYSCOMMAND, SC_RESTORE, 0);
		}
		saved_window_info_.style = GetWindowLong(native_window_handle, GWL_STYLE);
		saved_window_info_.ex_style = GetWindowLong(native_window_handle, GWL_EXSTYLE);
		GetWindowRect(native_window_handle, &saved_window_info_.window_rect);

#ifndef SCHLECHTER_STIL_FRAMED_WINDOW
		SetWindowLong(native_window_handle, GWL_STYLE,
			saved_window_info_.style & ~(WS_CAPTION | WS_THICKFRAME));//entfernt WS_CAPTION+ws_thickframe
		SetWindowLong(native_window_handle, GWL_EXSTYLE,
			saved_window_info_.ex_style & ~(WS_EX_DLGMODALFRAME |
			WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));//ist extended style
		//wenn ich das hier auskommentiere,kommt ein frame raus
#else
		SetWindowLong(native_window_handle, GWL_STYLE,
			saved_window_info_.style | WS_CAPTION | WS_THICKFRAME | WS_SYSMENU);
#endif
		// On expand, if we're given a window_rect, grow to it, otherwise do
		// not resize.

		MONITORINFO monitor_info;
		monitor_info.cbSize = sizeof(monitor_info);
		GetMonitorInfo(MonitorFromWindow(native_window_handle, MONITOR_DEFAULTTONEAREST),
			&monitor_info);//sucht wohl den richtigen Monitor aus,mit dem die APp am meisten(Schnittmenge) zu tun hat

		My_GFX_Rect window_rect(monitor_info.rcMonitor);
		SetWindowPos(native_window_handle, NULL, window_rect.x, window_rect.y,
			window_rect.width, window_rect.height,
			SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
#endif

	}

};
#endif