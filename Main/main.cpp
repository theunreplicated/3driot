#include <Windows.h>
#include "../window2/MessageLoop.cpp"
#include "my_gfx_rect.h"
#include "File_Parser.h"
#include "../window2/GLMain.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message)
	{

	case WM_CREATE:

		return 0;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_DESTROY:
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{

		case VK_ESCAPE:
			PostQuitMessage(0);
			return 0;

		}
		return 0;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);

	}

}	struct window_info{
	bool maximized;
	LONG style, ex_style;
	RECT window_rect;

};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{
	WNDCLASS wc;
	LPCSTR className = "hey";
	LPCSTR windowName = "hey";
	// register window class
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//einfach IDC_* ändern
	//	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//win-api.de
	wc.lpszMenuName = NULL;
	wc.lpszClassName = className;
	RegisterClass(&wc);

	//int sz=GetSystemMetrics(SM_CXSIZE);
	HWND native_window_handle = CreateWindow(
		className, windowName,
		NULL,
		0,0, 200, 200,
		NULL, NULL, hInstance, NULL);

	//http://stackoverflow.com/questions/2382464/win32-full-screen-and-hiding-taskbar
	//CHromium source
	window_info saved_window_info_;
	saved_window_info_.maximized = !!::IsZoomed(native_window_handle);
	if (saved_window_info_.maximized)
		::SendMessage(native_window_handle, WM_SYSCOMMAND, SC_RESTORE, 0);
	saved_window_info_.style = GetWindowLongA(native_window_handle, GWL_STYLE);
	saved_window_info_.ex_style = GetWindowLong(native_window_handle, GWL_EXSTYLE);
		GetWindowRect(native_window_handle, &saved_window_info_.window_rect);


		SetWindowLong(native_window_handle, GWL_STYLE,
			saved_window_info_.style & ~(WS_CAPTION | WS_THICKFRAME));
		SetWindowLong(native_window_handle, GWL_EXSTYLE,
			saved_window_info_.ex_style & ~(WS_EX_DLGMODALFRAME |
			WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));

		// On expand, if we're given a window_rect, grow to it, otherwise do
		// not resize.
		
			MONITORINFO monitor_info;
			monitor_info.cbSize = sizeof(monitor_info);
			GetMonitorInfo(MonitorFromWindow(native_window_handle, MONITOR_DEFAULTTONEAREST),
				&monitor_info);
			
			My_GFX_Rect window_rect(monitor_info.rcMonitor);
			SetWindowPos(native_window_handle, NULL, window_rect.x, window_rect.y,
				window_rect.width, window_rect.height,
				SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);


	::ShowWindow(native_window_handle,SW_SHOW);
	//Window wird nun gezeigt,Fullscreen,ok

	FileParser*ps = new FileParser("scene.shotgun");
	std::vector<THREEDObject> obj=ps->parse();

	(new Windows::MessageLoop())->GetMessage_Approach();
}