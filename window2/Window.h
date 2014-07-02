#ifndef WINDOW_H
#define WINDOW_H
#include <Windows.h>
#include "ApplicationWindow.h"
#include "WindowStructs.h"
#include "standard_window.h"
namespace Windows{
	class Window:public standard_window{
	private:
		void makeAppearBetter();
		ApplicationWindow* m_ApplicationWindow;
		//enum lpClassNames { BUTTON, EDIT };
	public:
		void ApplicationWindow_std_callback(HWND hWnd, WPARAM wParam, LPARAM lParam);
		Window(WindowNames<LPCSTR> names, WindowRect rect, DWORD dwStyle, ApplicationWindow*aw, DWORD dwExStyle = NULL);
		Window(WindowNames<LPCSTR> names, WindowRect rect, DWORD dwStyle, ApplicationWindow*aw, DWORD dwExStyle,HWND window_parent);//als extra parameter gehts net;-)
		HWND window_handle;
		void on(winproc_promise_event pe, winproc_callback_function callbackf);
		WindowRect Position_get();
		/*
		char *Text_get();
		int Text_set(LPCTSTR lpString);
		
		int Position_set(WindowRect rect, bool repaint = true);
		
		HDC DeviceContext_get();
		int DeviceContext_release(HDC device_context);//TODO:ohne arg,selbes wie _get
		RECT  Rect_get();
		int show(int show_command=SW_SHOW);
	*/
	};
}
#endif