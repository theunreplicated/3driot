#ifndef WINDOW_H
#define WINDOW_H
#include <Windows.h>
#include "ApplicationWindow.h"
#include "WindowStructs.h"
namespace Windows{
	class Window{
	private:
		ApplicationWindow* m_ApplicationWindow;
		//enum lpClassNames { BUTTON, EDIT };
	public:
		void ApplicationWindow_std_callback(HWND hWnd, WPARAM wParam, LPARAM lParam);
		Window(WindowNames<LPCSTR> names, WindowRect rect, DWORD dwStyle, ApplicationWindow*aw, DWORD dwExStyle = NULL);
		HWND window_handle;
		char *Text_get();
		int Text_set(LPCTSTR lpString);
		WindowRect Position_get();
		int Position_set(WindowRect rect,bool repaint=true);
		void on(winproc_promise_event pe, winproc_callback_function callbackf);
		HDC DeviceContext_get();
		int DeviceContext_release(HDC device_context);//TODO:ohne arg,selbes wie _get
		RECT  Rect_get();
	
	};
}
#endif