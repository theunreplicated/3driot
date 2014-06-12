#include "standard_window.h"
namespace Windows{


	standard_window::standard_window(HWND *wHandle,HWND *native_wHandle){
		window_handle = wHandle;
		native_window_handle = native_wHandle;
	}

	RECT  standard_window::Rect_get(){//vll.t entfernen//@deprecated
		RECT rect;
		GetWindowRect(*window_handle, &rect);
		return rect;
	}
	WindowRect standard_window::Position_get(){
		RECT rCtlWin;                   // Koordinaten des Controls

		POINT p0;

		GetWindowRect(*window_handle, &rCtlWin);  // Koordinaten relativ zum Parent Window und nicht zum

		// Ursprung des Screens, wie es fälschlich im SDK steht

		// hier lag mein Problem!

		//http://www.spieleprogrammierer.de/18-c-cplusplus-csharp-java-und-andere-sprachen/6669-verst%C3%A4ndnis-problem-mit-getclientrect-unter-win32/

		// Breite des Rahmens und Höhe der Titelleiste des Parent Windows berechnen

		p0.x = 0;
		p0.y = 0;                         // Ursprung der Dialog-Client area ...

		ClientToScreen(*native_window_handle, &p0);    // ... in Screenkoordinaten wandeln (Dialog-Handle verwenden)

		// --> p0.x = Breite der linken Border in Pixel

		// --> p0.y = Höhe derTitle bar in Pixel
		int w = rCtlWin.right - rCtlWin.left; int h = rCtlWin.bottom - rCtlWin.top;
		int x = rCtlWin.left - p0.x;
		int y = rCtlWin.top - p0.y;
		//int leftCtl = rectCli.left + rCtlWin.left;
		return{ w, h, x, y };
	}
	int standard_window::Position_set(WindowRect rect, bool repaint){
		return ::MoveWindow(*window_handle, rect.x, rect.y, rect.width, rect.height, repaint);

	}
	char * standard_window::Text_get(){

		int text_length = GetWindowTextLength(*window_handle);

		char*buffer = (char*)malloc(text_length);

		GetWindowText(*window_handle, buffer, text_length + 1);/*warum +1?ist von win-api.de,nach  msdn wird es sowieso niemals größer als text_length*/
		return buffer;
	}
	int standard_window::Text_set(LPCTSTR lpString){
		return SetWindowText(*window_handle, lpString);

	}
	

	HDC standard_window::DeviceContext_get(){
		return ::GetDC(*window_handle);

	}
	int standard_window::DeviceContext_release(HDC device_context){
		return ::ReleaseDC(*window_handle, device_context);

	}
	int standard_window::show(int show_command){
		return ::ShowWindow(*window_handle, show_command);

	}

};