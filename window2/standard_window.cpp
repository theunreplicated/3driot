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