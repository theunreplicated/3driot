#pragma once
#include "../../../Window.h"
class CheckBox{
private:
	Windows::ApplicationWindow*ApplicationWindow;
public:
	CheckBox(LPCSTR text, Windows::WindowRect rect, Windows::ApplicationWindow*aw, DWORD additional_styles=WS_VISIBLE);
	Windows::Window*window;
	void check();
	void uncheck();
	bool is_checked();
	static bool EVENT_IS_CHECKED(HWND global_wnd, WPARAM wParam, LPARAM lParam, HWND caller_wnd);
};