#ifndef Application_UI_CONTROL_MGR_H
#define Application_UI_CONTROL_MGR_H
#include "ApplicationWindow.h"
#include "Window.h"
#include "WindowStructs.h"
#include <Windows.h>
#include <vector>
#include <string>
//using std::vector;
typedef void(*ui_mouse_pos_callback_type)(int, int,int,int);
struct TripleEditWindow{
	Windows::Window* x,* y,* z;

};
class ApplicationUI_Control_Mgr{
public:
	ApplicationUI_Control_Mgr(Windows::ApplicationWindow* aw, int width, int height,Windows::Window*parent=NULL);
	static void addButtons(Windows::winproc_promise_event wpe);
	static void addEditControls();
	static void btn_add_row_cb(HWND hWnd, WPARAM wParam, LPARAM lParam);
	static void btn_action(HWND hWnd, WPARAM wParam, LPARAM lParam);
	static Windows::Window *static_draw_field;
	static Windows::Window* objects_list;
	static Windows::Window* open_file_btn;
	static Windows::Window*save_threed_objects;
	static Windows::Window*main_tab_control;
	static Windows::Window*dragdropbutton;
	void set_mouse_pos_callback(ui_mouse_pos_callback_type uim);
	//static void add_objects_list_child_btn(Windows::Window );
private:
	
	static std::vector<TripleEditWindow>windowInsts;
	static int edit_startpoint_h;
	static Windows::Window *new_row_add_button;
	static Windows::Window*action_button;
	static int m_width, m_height, editheight,padding;
	static Windows::ApplicationWindow *ApplicationWindow;
	static Windows::Window*m_parentWindow;
};

#endif