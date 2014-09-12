#ifndef WINDOW_STRUCTS_H
#define WINDOW_STRUCTS_H
#include <Windows.h>
#include <cmath>
namespace Windows{
	typedef  void(*winproc_callback_function)(HWND hWnd, WPARAM wParam, LPARAM lParam);
	typedef bool(*winproc_promise_event_func)(HWND global_wnd, WPARAM wParam, LPARAM lParam,HWND caller_wnd);
	struct winproc_promise_event{
		winproc_promise_event_func  wpef_callback;
		UINT invoke_on_message;
		bool use_window_check;
		HWND * wnd_ptr;
	};
	struct winproc_additional_data_struct{
		winproc_promise_event wpe;
		winproc_callback_function cbf;
	};
	enum CW_CLASS_TYPES {EDIT,BUTTON };//@TODO:in ui_control_mgr verwenden

	template <typename classNameType>
	struct WindowNames{
		classNameType lpClassName;
		classNameType  lpWindowName;
	
	};
	struct WindowRect{
		//	WindowRect() :width(0){};//struct ohne KonstruktOOOOR leider nur begrenzt einsetzbar,aber mit {} init werden alle anderen Values auf default-null gesetzt
		int width, height, x, y;
		void fromRect(RECT rect){//mit dem from* ist eigentlich schlechter Stil
			width = std::abs(rect.right - rect.left);
			height = std::abs(rect.bottom - rect.top);
			x = rect.left; y = rect.top;
		};
	};
	//CW_CLASS_TYPES cct="fd";	

}
#endif