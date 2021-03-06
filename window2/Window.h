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
		Window* m_window_parent;
		
		//enum lpClassNames { BUTTON, EDIT };
	public:
		Window(WindowNames<LPCSTR> names, WindowRect rect, DWORD dwStyle, Window*parent_window, DWORD dwExStyle=NULL, HMENU menu_id=NULL);
		Window(WindowNames<LPCWSTR> names, WindowRect rect, DWORD dwStyle, Window*parent_window, DWORD dwExStyle = NULL, HMENU menu_id = NULL);
		ApplicationWindow* m_ApplicationWindow;
		void ApplicationWindow_std_callback(HWND hWnd, WPARAM wParam, LPARAM lParam);
		//Window(WindowNames<LPCSTR> names, WindowRect rect, DWORD dwStyle, ApplicationWindow*aw, DWORD dwExStyle = NULL);
		//template <typename T_wn_types>
		Window(WindowNames<LPCSTR> names, WindowRect rect, DWORD dwStyle, ApplicationWindow*aw, DWORD dwExStyle = NULL,/*Window*window_parent = NULL,*/ HMENU menu_id = NULL);//als extra parameter gehts net;-)
		Window(WindowNames<LPCWSTR> names, WindowRect rect, DWORD dwStyle, ApplicationWindow*aw, DWORD dwExStyle = NULL, Window*window_parent = NULL, HMENU menu_id = NULL);
	
		void on(winproc_promise_event pe, winproc_promise_event_further_func callbackf);
		WindowRect Position_get(Position_Relative_to pos_relative=Position_Relative_to_Window);

	};
}
#endif