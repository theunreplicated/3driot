#include "ApplicationUI_Control_Mgr.h"
int ApplicationUI_Control_Mgr::m_width;
int ApplicationUI_Control_Mgr::m_height;
int ApplicationUI_Control_Mgr::editheight;
int ApplicationUI_Control_Mgr::padding;
int ApplicationUI_Control_Mgr::edit_startpoint_h;
using std::vector;
vector<TripleEditWindow> ApplicationUI_Control_Mgr::windowInsts;
Windows::ApplicationWindow *ApplicationUI_Control_Mgr::ApplicationWindow;
Windows::Window *ApplicationUI_Control_Mgr::new_row_add_button;
Windows::Window*ApplicationUI_Control_Mgr::action_button;
ApplicationUI_Control_Mgr::ApplicationUI_Control_Mgr(Windows::ApplicationWindow* aw, int width, int height){
	ApplicationWindow = aw;
	m_width = width;
	m_height = height;
	editheight = 20;
	padding = editheight + 20;
	edit_startpoint_h = 30;
}
void ApplicationUI_Control_Mgr::btn_add_row_cb(HWND hWnd, WPARAM wParam, LPARAM lParam){
	
	//addEditControls();
	//MessageBox(NULL,"fdsfs","fdfds",MB_OK);
	edit_startpoint_h += padding;
	addEditControls();
	Windows::WindowRect pos=new_row_add_button->Position_get();
	pos.y += padding;
	
	//dasgleiche f�r Action-Button//copy n paste//@TODO:in Funktion anstelle Copy n paste
	Windows::WindowRect pos2 = action_button->Position_get();
	pos2.y += padding;
	action_button->Position_set(pos2);//repaint auf false
	new_row_add_button->Position_set(pos);
	
	//pos.height

}
void ApplicationUI_Control_Mgr::addButtons(Windows::winproc_promise_event wpe){
	int editwidth = 100, editheight = 20, edit_startpoint_w = m_width - editwidth - 30, edit_startpoint_h = 30, padding = editheight + 20, padding_w = 20;
	new_row_add_button=new Windows::Window({ "button", "Neue Reihe hinzuf�gen" }, { 175, 30, edit_startpoint_w - ((editwidth + padding_w) * 1), edit_startpoint_h + 50 }, WS_CHILD | WS_VISIBLE, ApplicationWindow);
	//SetFocus(new_row_add_button->window_handle);
	action_button = new Windows::Window({ "button", "Actionnnn" }, { 175, 30, edit_startpoint_w - ((editwidth + padding_w) * 1), edit_startpoint_h + 50+padding }, WS_CHILD | WS_VISIBLE, ApplicationWindow);
	new_row_add_button->on(wpe, btn_add_row_cb);

}
void ApplicationUI_Control_Mgr::addEditControls(){
	using Windows::Window;
	int editwidth = 100,  edit_startpoint_w = m_width - editwidth - 30, padding_w = 20;
	Window*x=new Window( { "edit", "x" }, { editwidth, editheight,edit_startpoint_w - ((editwidth + padding_w) * 2), edit_startpoint_h }, WS_CHILD | WS_VISIBLE, ApplicationWindow);
	Window*y=new Window( { "edit", "y" }, { editwidth, editheight,edit_startpoint_w - ((editwidth + padding_w) * 1), edit_startpoint_h }, WS_CHILD | WS_VISIBLE, ApplicationWindow);
	Window*z=new Window({ "edit", "z" }, { editwidth, editheight,edit_startpoint_w, edit_startpoint_h }, WS_CHILD | WS_VISIBLE, ApplicationWindow);


	windowInsts.push_back({x,y,z});


}