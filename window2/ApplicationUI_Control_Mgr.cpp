#include "ApplicationUI_Control_Mgr.h"
#include "APIs\OS\Win\UI_Controls\CheckBox.h"
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
Windows::Window* ApplicationUI_Control_Mgr::objects_list;
Windows::Window* ApplicationUI_Control_Mgr::open_file_btn;
Windows::Window* ApplicationUI_Control_Mgr::save_threed_objects;

ui_mouse_pos_callback_type ui_mouse_pos_callback;
//updatewindow?
LRESULT CALLBACK draw_field_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	//@TODO:bei lbuttondown koordinaten(natürlich relativ zu dem Feld) hier,dann von diesem Punkt den entsprechenden OpenglGL-Pixel ausrechen,diesen einen dann glreadpixel übergeben,dass die depth werte ausliest,und da ich es so machen will,dass über den depth wert die id-des objekts gespeicert wird(textur) könnte man das obj so wählen//@TODO:verbesssertes subclassing
	switch (message){//@TODO:dann aufpassen,ob die kkoirdnaten gena
		//@TODO:vllt .was anderes als lbtndown
	case WM_LBUTTONDOWN:{
		DWORD mousepos=::GetMessagePos();
		POINTS p = MAKEPOINTS(mousepos);
		
		LPPOINT pr= new tagPOINT; pr->x = p.x; pr->y = p.y;//die end-position sind nicht so genau,ist aber jetzt zuerst mal egal,und zwar so die angebegenen daten -5
		::ScreenToClient(hWnd,pr);
		std::string mouse_pos = std::to_string((*pr).x) + "-" + std::to_string((*pr).y); ui_mouse_pos_callback(pr->x,pr->y);
		return true/*MessageBoxA(NULL, mouse_pos.c_str(), "fddfs", MB_OK);*/; }
		break;
	default:
		return DefWindowProc(hWnd,message,wParam,lParam);
	}
	//@TODO:org proc aufrufen
}
void oncheck(HWND hWnd, WPARAM wParam, LPARAM lParam){
	::MessageBoxA(NULL,"dd","ddd",MB_OK);
}
ApplicationUI_Control_Mgr::ApplicationUI_Control_Mgr(Windows::ApplicationWindow* aw, int width, int height){
	ApplicationWindow = aw;
	m_width = width;
	m_height = height;
	editheight = 20;
	padding = editheight + 20;
	edit_startpoint_h = 30;
	//@das wäre am besten einheitliche variablenname für gleiche typen übers ganze projekt(auch beachtung von member)
	static_draw_field = new Windows::Window({ "STATIC", "" }, { 600,700, 0, 0 }, WS_CHILD | WS_VISIBLE, ApplicationWindow, WS_EX_CLIENTEDGE/*NULL*/);
	SetWindowLongPtr(static_draw_field->window_handle,
		GWLP_WNDPROC, (LONG_PTR)draw_field_proc);
	CheckBox*cb = new CheckBox("text", {20,20,710,150},ApplicationWindow);
	cb->check();

	
	//::SetFocus(wnd);
	//cb->window->on({ cb->EVENT_IS_CHECKED, WM_COMMAND, true },oncheck);
	open_file_btn = new Windows::Window({ "BUTTON", "Mesh importieren" }, { 150, 70, 610, 0 }, WS_CHILD | WS_VISIBLE , ApplicationWindow, /*WS_EX_CLIENTEDGE*/NULL);
	save_threed_objects = new Windows::Window({ "BUTTON", "RenderObjects speichern" }, { 150, 70, 780, 0 }, WS_CHILD | WS_VISIBLE, ApplicationWindow, WS_EX_CLIENTEDGE);
	//WNDPROC OldWndProc = (WNDPROC)SetWindowLongA(f->window_handle,
		//GWLP_WNDPROC, (LONG_PTR)WndProcedure);
	//Windows::Window *btn = new Windows::Window({ "BUTTON", "hi" }, { 300, 500, 0, 0 }, WS_CHILD | WS_VISIBLE | WS_VSCROLL, ApplicationWindow, WS_EX_CLIENTEDGE,f->window_handle);
	
}
void ApplicationUI_Control_Mgr::set_mouse_pos_callback(ui_mouse_pos_callback_type uim){ ui_mouse_pos_callback = uim; }
void ApplicationUI_Control_Mgr::btn_add_row_cb(HWND hWnd, WPARAM wParam, LPARAM lParam){
	
	//addEditControls();
	//MessageBox(NULL,"fdsfs","fdfds",MB_OK);
	edit_startpoint_h += padding;
	addEditControls();
	Windows::WindowRect pos=new_row_add_button->Position_get();
	pos.y += padding;
	
	//dasgleiche für Action-Button//copy n paste//@TODO:in Funktion anstelle Copy n paste
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

	//static_draw_field->DeviceContext_release(hDC);
}
void ApplicationUI_Control_Mgr::addButtons(Windows::winproc_promise_event wpe){
	int editwidth = 100, editheight = 20, edit_startpoint_w = m_width - editwidth - 30, edit_startpoint_h = 30, padding = editheight + 20, padding_w = 20;
	new_row_add_button = new Windows::Window({ "button", "Neue Reihe hinzufügen" }, { 175, 30, edit_startpoint_w - ((editwidth + padding_w) * 1), edit_startpoint_h + 50 }, WS_CHILD | WS_VISIBLE, ApplicationWindow);
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