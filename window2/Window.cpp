#include "Window.h"
#include <functional>
#include <Windows.h>
namespace Windows{

	//template <typename T_wn_types>
	Window::Window(WindowNames<LPCSTR> names, WindowRect rect, DWORD dwStyle, ApplicationWindow*aw, DWORD dwExStyle, HWND window_parent)/* :standard_window(&window_handle, &window_parent)*/{

		m_ApplicationWindow = aw;
		window_handle = CreateWindowEx(dwExStyle,
			names.lpClassName,
			names.lpWindowName,    // <- das ist der Inhalt der Editfelds
			/*WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE |
			ES_AUTOVSCROLL*/dwStyle,
			rect.x, rect.y, rect.width, rect.height,
			(window_parent==NULL ? aw->window_handle:window_parent),
			NULL,
			/*((LPCREATESTRUCT)lParam)->*/aw->m_hInstance,
			NULL);
		makeAppearBetter();

	}
	//function param inheritance h�tte ich hier gerne,und besserer Compiler-support dabei ohne das <LPCSTR> jedes mal zu schreiben
	Window::Window(WindowNames<LPCWSTR> names, WindowRect rect, DWORD dwStyle, ApplicationWindow*aw, DWORD dwExStyle, HWND window_parent) /*:standard_window(&window_handle, &window_parent)*/{

		m_ApplicationWindow = aw;
		window_handle = CreateWindowExW(dwExStyle,
			names.lpClassName,
			names.lpWindowName,    // <- das ist der Inhalt der Editfelds
			/*WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE |
			ES_AUTOVSCROLL*/dwStyle,
			rect.x, rect.y, rect.width, rect.height,
			(window_parent == NULL ? aw->window_handle : window_parent),
			NULL,
			/*((LPCREATESTRUCT)lParam)->*/aw->m_hInstance,
			NULL);
		makeAppearBetter();

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
	WindowRect Window::Position_get(){//funzt in ApplicationWindow net,ich wei� aber warum//@TODO:dabei anderes window parent als applicationwindow+evtl. subcalssing erm�glichen von messageloop f�r vllt. scrolling(functionx.com? )
		//so k�nnte es auch gehen: http://stackoverflow.com/questions/18034975/how-do-i-find-position-of-a-win32-control-window-relative-to-its-parent-window
		RECT rCtlWin;                   // Koordinaten des Controls
		//@TODO:anderes parent als applicationwindow erlauben
		POINT p0;

		GetWindowRect(window_handle, &rCtlWin);  // Koordinaten relativ zum Parent Window und nicht zum

		// Ursprung des Screens, wie es f�lschlich im SDK steht

		// hier lag mein Problem!

		//http://www.spieleprogrammierer.de/18-c-cplusplus-csharp-java-und-andere-sprachen/6669-verst%C3%A4ndnis-problem-mit-getclientrect-unter-win32/

		// Breite des Rahmens und H�he der Titelleiste des Parent Windows berechnen

		p0.x = 0;
		p0.y = 0;                         // Ursprung der Dialog-Client area ...

		ClientToScreen(m_ApplicationWindow->window_handle, &p0);    // ... in Screenkoordinaten wandeln (Dialog-Handle verwenden)

		// --> p0.x = Breite der linken Border in Pixel

		// --> p0.y = H�he derTitle bar in Pixel
		int w = rCtlWin.right - rCtlWin.left; int h = rCtlWin.bottom - rCtlWin.top;
		int x = rCtlWin.left - p0.x;
		int y = rCtlWin.top - p0.y;
		//int leftCtl = rectCli.left + rCtlWin.left;
		return{ w, h, x, y };
	}
};