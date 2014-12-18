#include "ApplicationUI_Control_Mgr.h"
#include "APIs\OS\Win\UI_Controls\CheckBox.h"
#include "APIs\OS\Win\UI_Controls\ComboBox.h"
#include "APIs\OS\Win\UI_Controls\TreeView.h"
#include <CommCtrl.h>
int ApplicationUI_Control_Mgr::m_width;
int ApplicationUI_Control_Mgr::m_height;
int ApplicationUI_Control_Mgr::editheight;
int ApplicationUI_Control_Mgr::padding;
int ApplicationUI_Control_Mgr::edit_startpoint_h;
using std::vector;
vector<TripleEditWindow> ApplicationUI_Control_Mgr::windowInsts;
Windows::ApplicationWindow *ApplicationUI_Control_Mgr::ApplicationWindow;
Windows::Window* ApplicationUI_Control_Mgr::main_window;
Windows::Window *ApplicationUI_Control_Mgr::new_row_add_button;
Windows::Window*ApplicationUI_Control_Mgr::action_button;
Windows::Window *ApplicationUI_Control_Mgr::static_draw_field;
Windows::Window*ApplicationUI_Control_Mgr::main_tab_control;
Windows::Window* ApplicationUI_Control_Mgr::objects_list;
Windows::Window* ApplicationUI_Control_Mgr::open_file_btn;
Windows::Window* ApplicationUI_Control_Mgr::save_threed_objects;
Windows::Window* ApplicationUI_Control_Mgr::m_parentWindow;
Windows::Window* ApplicationUI_Control_Mgr::dragdropbutton;
ui_mouse_pos_callback_type ui_mouse_pos_callback;
//updatewindow?
//@TODO:eigentliches hook_proc aufrufen,deshalb wohl auch probleme mit diesem Window
LRESULT CALLBACK draw_field_proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){

	//@TODO:bei lbuttondown koordinaten(natürlich relativ zu dem Feld) hier,dann von diesem Punkt den entsprechenden OpenglGL-Pixel ausrechen,diesen einen dann glreadpixel übergeben,dass die depth werte ausliest,und da ich es so machen will,dass über den depth wert die id-des objekts gespeicert wird(textur) könnte man das obj so wählen//@TODO:verbesssertes subclassing
	switch (message){//@TODO:dann aufpassen,ob die kkoirdnaten gena
		//@TODO:vllt .was anderes als lbtndown
	/*case WM_KEYDOWN:
		MessageBox(NULL,"fds","fds",MB_OK);
		break;*/
	//case WM_MOUSEMOVE: ::MessageBox(NULL,"fd","fd",MB_APPLMODAL); break;
	case WM_LBUTTONDOWN:{
		//::SetFocus(hWnd);//@TODO:setfocus auf das,dann wohl tastatureingaben darauf lenken,aber vemutlich global gewollt,also das andere verhindern vom fokus bekommen
		RECT rect;
		GetClientRect(hWnd,&rect);
		DWORD mousepos=::GetMessagePos();
		POINTS p = MAKEPOINTS(mousepos);
		//http://gamedev.stackexchange.com/questions/29977/how-do-i-get-the-correct-values-from-glreadpixels-in-opengl-3-0
		//@TODO:gucken->da,warhscheinlich falsche koordinaten
		LPPOINT pr= new tagPOINT; pr->x = p.x; pr->y = p.y;//die end-position sind nicht so genau,ist aber jetzt zuerst mal egal,und zwar so die angebegenen daten -5
		::ScreenToClient(hWnd,pr);
		//http://www.cplusplus.com/forum/windows/102524/
		int width = std::abs(rect.right - rect.left);
		int height = std::abs(rect.bottom - rect.top);//betrag ist denk ich sicherer,macht aber glaub ich keinen Sinn //@TODO:in dem anderen Code die woth richtig berechnen
		ui_mouse_pos_callback(pr->x, pr->y,width,height);
		//std::string mouse_pos = std::to_string((*pr).x) + "-" + std::to_string((*pr).y); 
		
		return true/*MessageBoxA(NULL, mouse_pos.c_str(), "fddfs", MB_OK);*/; }
		break;
	default:
		return DefWindowProc(hWnd,message,wParam,lParam);//@TODO:defwindowproc ersetzen
	}
	//@TODO:org proc aufrufen
}
HWND DoCreateTabControl(Windows::standard_window *w, HINSTANCE hInstance)
{//http://msdn.microsoft.com/en-us/library/windows/desktop/hh298367(v=vs.85).aspx
	RECT rcClient;
	INITCOMMONCONTROLSEX icex;
	HWND hwndTab;
	TCITEM tie;
	int i;//TCHAR anstatt LPCSTR
	TCHAR achTemp[256];  // Temporary buffer for strings.

	// Initialize common controls.
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_TAB_CLASSES;
	InitCommonControlsEx(&icex);

	// Get the dimensions of the parent window's client area, and 
	// create a tab control child window of that size. Note that g_hInst
	// is the global instance handle.
	/*GetClientRect(hwndParent, &rcClient);
	hwndTab = CreateWindow(WC_TABCONTROL, TEXT(""),
	WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
	700, 500, rcClient.right, rcClient.bottom,
	hwndParent, NULL, hInstance, NULL);
	*/
	hwndTab = w->window_handle;

	if (hwndTab == NULL)
	{
		return NULL;
	}

	// Add tabs for each day of the week. 
	tie.mask = TCIF_TEXT /*| TCIF_IMAGE*/;
	tie.iImage = -1;
	tie.pszText = "hallo";

	TabCtrl_InsertItem(hwndTab, 0, &tie);
	tie.pszText = "2";
	if (TabCtrl_InsertItem(hwndTab, 1, &tie) == -1)
	{
		DestroyWindow(hwndTab);
		return NULL;
	}

	return hwndTab;
}
ApplicationUI_Control_Mgr::ApplicationUI_Control_Mgr(Windows::Window* mw, int width, int height,Windows::Window*parent){
//	ApplicationWindow = aw;// m_parentWindow = parent;
	m_width = width; main_window = mw;
	m_height = height;
	editheight = 20;
	padding = editheight + 20;
	edit_startpoint_h = 30; unsigned int hoehhe_verschiebung_a_cause_de_tabs = 30;
	//
	

//	main_tab_control = new Windows::Window({ WC_TABCONTROL, "" }, mw->ClientRect_get(), WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE, mw);
//	DoCreateTabControl(main_tab_control, mw->m_hInstance);
	//parent = main_tab_control;
	
	//@das wäre am besten einheitliche variablenname für gleiche typen übers ganze projekt(auch beachtung von member)
	static_draw_field = new Windows::Window({ "STATIC", "" }, { 600,700, 10, hoehhe_verschiebung_a_cause_de_tabs }, WS_CHILD | WS_VISIBLE, mw, WS_EX_CLIENTEDGE/*NULL*/);
	SetWindowLongPtr(static_draw_field->window_handle,
		GWLP_WNDPROC, (LONG_PTR)draw_field_proc);


	
	Windows::Window* combox = new Windows::Window({ WC_COMBOBOX, "" }, { 200, 200, 750, 300 }, CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE,mw);
	HWND hWndComboBox = combox->window_handle;
	Combo_Box*cb1 = new Combo_Box(&hWndComboBox);
	cb1->items->add("hallo");
	cb1->items->add("hallo2");

	Windows::Window* treev = new Windows::Window({ WC_TREEVIEW, "" }, { 200, 200, 750, 500 }, WS_VISIBLE | TVS_EDITLABELS | WS_CHILD | WS_GROUP | WS_TABSTOP | WS_BORDER | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES | TVS_SHOWSELALWAYS | TVS_INFOTIP,mw);
	Tree_View*tv = new Tree_View(treev->window_handle);
	auto curent_x_factor/*;-)*/ = tv->items->add("anti-aliasing-techniken");
	auto mlaa=	curent_x_factor->add("morphological-alising");
	mlaa->add("MLAA"); mlaa->add("SMAA(Subpixel )"); curent_x_factor->add("Multisampling"); curent_x_factor->add("FXAA");

	//::SetFocus(wnd);
	//cb->window->on({ cb->EVENT_IS_CHECKED, WM_COMMAND, true },oncheck);
	open_file_btn = new Windows::Window({ "BUTTON", "Mesh importieren" }, { 150, 70, 610, hoehhe_verschiebung_a_cause_de_tabs }, WS_CHILD | WS_VISIBLE,mw, /*WS_EX_CLIENTEDGE*/NULL );//bei anderem parent andere message loop?//@TODO:warum parent nicht geht
	save_threed_objects = new Windows::Window({ "BUTTON", "RenderObjects speichern" }, { 150, 70, 780, hoehhe_verschiebung_a_cause_de_tabs }, WS_CHILD | WS_VISIBLE, mw, WS_EX_CLIENTEDGE);
	//WNDPROC OldWndProc = (WNDPROC)SetWindowLongA(f->window_handle,
		//GWLP_WNDPROC, (LONG_PTR)WndProcedure);
	dragdropbutton = new Windows::Window({ "BUTTON", "dragdrop" }, { 70,50, 800, 100 }, WS_CHILD | WS_VISIBLE , mw, WS_EX_CLIENTEDGE);

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

	static_draw_field->DeviceContext_release(hDC);
}
void ApplicationUI_Control_Mgr::addButtons(Windows::winproc_promise_event wpe){
	int editwidth = 100, editheight = 20, edit_startpoint_w = m_width - editwidth - 30, edit_startpoint_h = 30, padding = editheight + 20, padding_w = 20;
	new_row_add_button = new Windows::Window({ "button", "Neue Reihe hinzufügen" }, { 175, 30, edit_startpoint_w - ((editwidth + padding_w) * 1), edit_startpoint_h + 50 }, WS_CHILD | WS_VISIBLE, main_window);
	//SetFocus(new_row_add_button->window_handle);
	action_button = new Windows::Window({ "button", "Actionnnn" }, { 175, 30, edit_startpoint_w - ((editwidth + padding_w) * 1), edit_startpoint_h + 50+padding }, WS_CHILD | WS_VISIBLE, main_window);
	new_row_add_button->on(wpe, btn_add_row_cb);
	action_button->on(wpe,btn_action);


}
void ApplicationUI_Control_Mgr::addEditControls(){
	using Windows::Window;
	int editwidth = 100,  edit_startpoint_w = m_width - editwidth - 30, padding_w = 20;
	Window*x=new Window( { "edit", "x" }, { editwidth, editheight,edit_startpoint_w - ((editwidth + padding_w) * 2), edit_startpoint_h }, WS_CHILD | WS_VISIBLE, main_window,WS_EX_CLIENTEDGE);
	Window*y = new Window({ "edit", "y" }, { editwidth, editheight, edit_startpoint_w - ((editwidth + padding_w) * 1), edit_startpoint_h }, WS_CHILD | WS_VISIBLE, main_window, WS_EX_CLIENTEDGE);
	Window*z = new Window({ "edit", "z" }, { editwidth, editheight, edit_startpoint_w, edit_startpoint_h }, WS_CHILD | WS_VISIBLE, main_window, WS_EX_CLIENTEDGE);


	windowInsts.push_back({x,y,z});


}