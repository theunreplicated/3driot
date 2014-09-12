#ifndef WINDOW_H
#define WINDOW_H
#include <Windows.h>
#include "ApplicationWindow.h"
#include "WindowStructs.h"
#include "standard_window.h"

namespace Windows{
	enum Position_Relative_to{ Position_Relative_to_Window, Position_Relative_to_Parent };
	class Window:public standard_window{
	private:
		standard_window* m_window_parent;
		
		//enum lpClassNames { BUTTON, EDIT };
	public:
		HINSTANCE m_hInstance;
		ApplicationWindow* m_ApplicationWindow;
		void ApplicationWindow_std_callback(HWND hWnd, WPARAM wParam, LPARAM lParam);
		//Window(WindowNames<LPCSTR> names, WindowRect rect, DWORD dwStyle, ApplicationWindow*aw, DWORD dwExStyle = NULL);
		//template <typename T_wn_types>
		Window(WindowNames<LPCSTR> names, WindowRect rect, DWORD dwStyle, ApplicationWindow*aw, DWORD dwExStyle = NULL, standard_window* window_parent = NULL, HMENU menu_id = NULL);//als extra parameter gehts net;-)
		Window(WindowNames<LPCWSTR> names, WindowRect rect, DWORD dwStyle, ApplicationWindow*aw, DWORD dwExStyle = NULL, standard_window*window_parent = NULL, HMENU menu_id = NULL);
		
		void on(winproc_promise_event pe, winproc_callback_function callbackf);
		WindowRect Position_get(Position_Relative_to pos_relative=Position_Relative_to_Window);
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