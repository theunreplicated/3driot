#ifndef Application_UI_CONTROL_MGR_H
#define Application_UI_CONTROL_MGR_H
#include "ApplicationWindow.h"
#include "Window.h"
#include "WindowStructs.h"
#include <Windows.h>
#include <vector>
using std::vector;
struct TripleEditWindow{
	Windows::Window x, y, z;

};
class ApplicationUI_Control_Mgr{
public:
	ApplicationUI_Control_Mgr(Windows::ApplicationWindow* aw, int width, int height);
	static void addButtons(Windows::winproc_promise_event wpe);
	static void addEditControls();
	static void btn_add_row_cb(HWND hWnd, WPARAM wParam, LPARAM lParam);
private:
	vector<TripleEditWindow>windowInsts;
	static int edit_startpoint_h;
	static Windows::Window *new_row_add_button;
	static int m_width, m_height, editheight,padding;
	static Windows::ApplicationWindow *ApplicationWindow;
};

#endif