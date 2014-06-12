#include "Window.h"
#include <functional>
#include <Windows.h>
namespace Windows{
	Window::Window( WindowNames<LPCSTR> names, WindowRect rect, DWORD dwStyle, ApplicationWindow*aw,DWORD dwExStyle):standard_window(&window_handle,&aw->native_window_handle){
		m_ApplicationWindow = aw;
		window_handle = CreateWindowEx(dwExStyle,
			names.lpClassName,
			names.lpWindowName,    // <- das ist der Inhalt der Editfelds
			/*WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE |
			ES_AUTOVSCROLL*/dwStyle,
			rect.x,rect.y, rect.width,rect.height,
			aw->native_window_handle,
			NULL,
			/*((LPCREATESTRUCT)lParam)->*/aw->m_hInstance,
			NULL);

		NONCLIENTMETRICS ncm;//http://stackoverflow.com/questions/3323541/how-can-i-make-the-win32-api-window-more-modern-looking
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
		HFONT hFont = ::CreateFontIndirect(&ncm.lfMessageFont);
		::SendMessage(window_handle, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

		//standard_window(window_handle,aw->native_window_handle);
	}
	void Window_ApplicationWindow_std_callback(HWND hWnd, WPARAM wParam, LPARAM lParam){
		MessageBox(NULL, "dssd---", "dsds", MB_OK);

	}
	void Window::on(winproc_promise_event pe, winproc_callback_function callbackf){
		//m_ApplicationWindow->addOnMessageInvoke(pe.invoke_on_message, Window_ApplicationWindow_std_callback);
		winproc_additional_data_struct wads;
		wads.cbf = callbackf;
		winproc_promise_event wpe;
		pe.wnd_ptr = &window_handle;
		wpe = pe;
		wads.wpe = wpe;
		m_ApplicationWindow->additional_winproc_data.push_back(wads);

	}
};