#include "standard_window.h"
#include <stdexcept>
namespace Windows{


	//standard_window::standard_window(HWND *wHandle,HWND *native_wHandle){
		//window_handle = wHandle;
		//native_window_handle = native_wHandle;
//	}
	void standard_window::makeAppearBetter(){//schlechter name
		NONCLIENTMETRICS ncm;//http://stackoverflow.com/questions/3323541/how-can-i-make-the-win32-api-window-more-modern-looking
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
		::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
		HFONT hFont = ::CreateFontIndirect(&ncm.lfMessageFont);
		::SendMessage(window_handle, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

	}
	RECT  standard_window::Rect_get(){//vll.t entfernen//@deprecated
		::RECT rect;
		::GetWindowRect(window_handle, &rect);
		return rect;
	}
	
	int standard_window::Position_set(WindowRect rect, bool repaint){
		return ::MoveWindow(window_handle, rect.x, rect.y, rect.width, rect.height, repaint);

	}
	char * standard_window::Text_get(){

		int text_length = ::GetWindowTextLengthA(window_handle);

		//char*buffer = new char[text_length*sizeof(char)/*sizeif char müsste 1 sein,durch(fall(oder freier Fall??)) müsste so auch stimmen*/];
		char*buffer = static_cast<char*>(malloc(text_length));
		if (!buffer){ throw std::runtime_error("Out of memoey-malloc failed"); }
		//http://programmersheaven.com/discussion/114501/what-s-the-real-size-of-char
		::GetWindowText(window_handle, buffer, text_length + 1);/*warum +1?ist von win-api.de,nach  msdn wird es sowieso niemals größer als text_length*/
		return buffer;
	}
	int standard_window::Text_set(LPCTSTR lpString){
		return ::SetWindowText(window_handle, lpString);

	}
	

	HDC standard_window::DeviceContext_get(){
		return ::GetDC(window_handle);

	}
	int standard_window::DeviceContext_release(HDC device_context){
		return ::ReleaseDC(window_handle, device_context);

	}
	int standard_window::show(int show_command){
		return ::ShowWindow(window_handle, show_command);

	}

};