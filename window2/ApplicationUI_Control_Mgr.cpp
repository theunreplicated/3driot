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
Windows::Window *ApplicationUI_Control_Mgr::static_draw_field;
ApplicationUI_Control_Mgr::ApplicationUI_Control_Mgr(Windows::ApplicationWindow* aw, int width, int height){
	ApplicationWindow = aw;
	m_width = width;
	m_height = height;
	editheight = 20;
	padding = editheight + 20;
	edit_startpoint_h = 30;
	static_draw_field = new Windows::Window({ "STATIC", "" }, { 600,700, 0, 0 }, WS_CHILD | WS_VISIBLE, ApplicationWindow, WS_EX_CLIENTEDGE/*NULL*/);
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
void ApplicationUI_Control_Mgr::btn_action(HWND hWnd, WPARAM wParam, LPARAM lParam){

//	int cx = GetSystemMetrics(SM_CXSCREEN);
	//int cy = GetSystemMetrics(SM_CYSCREEN);
	//jetzt unwichtig
	HDC hDC = static_draw_field->DeviceContext_get();

	//
	/*std::string s = std::to_string(value_x);http://stackoverflow.com/questions/10847237/how-to-convert-from-int-to-char
	char const *pchar = s.c_str();  //use char const* as target type
	MessageBox(NULL, pchar, pchar, MB_OK);/*
	*/
	int iteration_count = 0;
	for (TripleEditWindow data : windowInsts){
		int value_x = atoi(data.x->Text_get());
		int value_y = atoi(data.y->Text_get());
		int value_z = atoi(data.z->Text_get());
		RECT rect;
		rect.left = 400;
		rect.top = data.z->Position_get().y;
		const char* message = "My First Window";
		DrawText(hDC, message, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
		iteration_count++;
	}
	iteration_count = 0;

	static_draw_field->DeviceContext_release(hDC);
}
void ApplicationUI_Control_Mgr::addButtons(Windows::winproc_promise_event wpe){
	int editwidth = 100, editheight = 20, edit_startpoint_w = m_width - editwidth - 30, edit_startpoint_h = 30, padding = editheight + 20, padding_w = 20;
	new_row_add_button=new Windows::Window({ "button", "Neue Reihe hinzuf�gen" }, { 175, 30, edit_startpoint_w - ((editwidth + padding_w) * 1), edit_startpoint_h + 50 }, WS_CHILD | WS_VISIBLE, ApplicationWindow);
	//SetFocus(new_row_add_button->window_handle);
	action_button = new Windows::Window({ "button", "Actionnnn" }, { 175, 30, edit_startpoint_w - ((editwidth + padding_w) * 1), edit_startpoint_h + 50+padding }, WS_CHILD | WS_VISIBLE, ApplicationWindow);
	new_row_add_button->on(wpe, btn_add_row_cb);
	action_button->on(wpe,btn_action);

}
void ApplicationUI_Control_Mgr::addEditControls(){
	using Windows::Window;
	int editwidth = 100,  edit_startpoint_w = m_width - editwidth - 30, padding_w = 20;
	Window*x=new Window( { "edit", "x" }, { editwidth, editheight,edit_startpoint_w - ((editwidth + padding_w) * 2), edit_startpoint_h }, WS_CHILD | WS_VISIBLE, ApplicationWindow,WS_EX_CLIENTEDGE);
	Window*y = new Window({ "edit", "y" }, { editwidth, editheight, edit_startpoint_w - ((editwidth + padding_w) * 1), edit_startpoint_h }, WS_CHILD | WS_VISIBLE, ApplicationWindow, WS_EX_CLIENTEDGE);
	Window*z = new Window({ "edit", "z" }, { editwidth, editheight, edit_startpoint_w, edit_startpoint_h }, WS_CHILD | WS_VISIBLE, ApplicationWindow, WS_EX_CLIENTEDGE);


	windowInsts.push_back({x,y,z});


}