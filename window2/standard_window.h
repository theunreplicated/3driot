#ifndef INC_standard_Window_H
#define INC_standard_Window_H

#include <Windows.h>
#include "WindowStructs.h"
namespace Windows{
	class standard_window{
	private:
		HWND *window_handle, *native_window_handle;
	public:
		standard_window(HWND *wHandle, HWND *native_wHandle);
		
		char *Text_get();
		int Text_set(LPCTSTR lpString);
		
		int Position_set(WindowRect rect, bool repaint = true);
		void on(winproc_promise_event pe, winproc_callback_function callbackf);
		HDC DeviceContext_get();
		int DeviceContext_release(HDC device_context);//TODO:ohne arg,selbes wie _get
		RECT  Rect_get();
		//http://stackoverflow.com/questions/17488826/the-meaning-of-sw-show-and-sw-shownormal
		int show(int show_command = SW_SHOW/*NORMAL*//*da wohl auch show/hide möglich sein soll,nur vllt. ist das dann mit dem Restoren falsch*/);

	};
}
#endif