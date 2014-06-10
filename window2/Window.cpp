#include "Window.h"
#include <functional>
#include <Windows.h>
namespace Windows{
	Window::Window( WindowNames<LPCSTR> names, WindowRect rect, DWORD dwStyle, ApplicationWindow*aw,DWORD dwExStyle){
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
	}
	WindowRect Window::Position_get(){
		RECT rCtlWin;                   // Koordinaten des Controls

		POINT p0;

		GetWindowRect(window_handle, &rCtlWin);  // Koordinaten relativ zum Parent Window und nicht zum

		// Ursprung des Screens, wie es fälschlich im SDK steht

		// hier lag mein Problem!

		//http://www.spieleprogrammierer.de/18-c-cplusplus-csharp-java-und-andere-sprachen/6669-verst%C3%A4ndnis-problem-mit-getclientrect-unter-win32/

		// Breite des Rahmens und Höhe der Titelleiste des Parent Windows berechnen

		p0.x = 0;
		p0.y = 0;                         // Ursprung der Dialog-Client area ...

		ClientToScreen(m_ApplicationWindow->native_window_handle, &p0);    // ... in Screenkoordinaten wandeln (Dialog-Handle verwenden)

		// --> p0.x = Breite der linken Border in Pixel

		// --> p0.y = Höhe derTitle bar in Pixel
		int w = rCtlWin.right - rCtlWin.left; int h = rCtlWin.bottom - rCtlWin.top;
		int x = rCtlWin.left - p0.x;
		int y = rCtlWin.top - p0.y;
		//int leftCtl = rectCli.left + rCtlWin.left;
		return{ w, h,x,y };
	}
	int Window::Position_set(WindowRect rect, bool repaint){
		return ::MoveWindow(window_handle,rect.x,rect.y,rect.width,rect.height,repaint);

	}
	char * Window::Text_get(){

		int text_length = GetWindowTextLength(window_handle);

		char*buffer=(char*)malloc(text_length);

		GetWindowText(window_handle, buffer, text_length + 1);/*warum +1?ist von win-api.de,nach  msdn wird es sowieso niemals größer als text_length*/
		return buffer;
	}
	int Window::Text_set(LPCTSTR lpString){
		return SetWindowText(window_handle,lpString);

	}
	void Window_ApplicationWindow_std_callback(HWND hWnd, WPARAM wParam, LPARAM lParam){
		MessageBox(NULL, "dssd---","dsds",MB_OK);

	}
	void Window::on(winproc_promise_event pe, winproc_callback_function callbackf){
		//m_ApplicationWindow->addOnMessageInvoke(pe.invoke_on_message, Window_ApplicationWindow_std_callback);
		winproc_additional_data_struct wads;
		wads.cbf = callbackf;
		winproc_promise_event wpe;
		pe.wnd_ptr = &window_handle;
		wpe= pe;
		wads.wpe = wpe;
		m_ApplicationWindow->additional_winproc_data.push_back(wads);
		
	}
	HDC Window::DeviceContext_get(){
		return ::GetDC(window_handle);
		
	}
	int Window::DeviceContext_release(HDC device_context){
		return ::ReleaseDC(window_handle,device_context);

	}
};