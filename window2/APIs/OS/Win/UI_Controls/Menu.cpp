//@TODO: komplettes rewrite,n haufen unnötiger Code gibts hier,und viel copy and paste

#define MENU_ITEMS_STARTWERT 2000 //markos vom namen möglichst weit abschotten wäre besser,aber jetzt unwichtig,es gibt größere Probleme;-)und zwar dass die Erde keine Scheibe ist.nein,ich meins hier direkt lokal vom Ort im dreckigen/batschigen Code
#include "Menu.h"
unsigned int Menu::menu_items_counter = MENU_ITEMS_STARTWERT;
std::vector<Windows::winproc_callback_function> Menu::callbackfunctions;
using std::vector;
void Menu::MENU_IS_MENU_ITEM/*@TODO:klein schreiben*/(HWND hWnd, WPARAM wParam, LPARAM lParam){
	auto lw = LOWORD(wParam);
	if ((lw >= MENU_ITEMS_STARTWERT)&&((callbackfunctions.size()-1) >= (lw-MENU_ITEMS_STARTWERT))){//falls lw in range(Pferderanch),größer >= müsste richtig sein
		
		callbackfunctions[lw - MENU_ITEMS_STARTWERT](hWnd, wParam, lParam);

	}


}

Menu_Item::Menu_Item(LPCSTR name, Windows::winproc_callback_function callbfunc, UINT additional_flag){
	m_callbfunc = callbfunc; m_additional_flags = additional_flag; m_name = name;

}
void Menu_Item::callback_create(HMENU parent_menu, Menu* menu_ref){

	AppendMenu(parent_menu,m_additional_flags| MF_STRING,menu_ref->get_item_id(m_callbfunc), m_name);
}

void PopUp_Menu::callback_create(HMENU parent_menu,Menu* menu_ref){
	menu_handle = ::CreatePopupMenu(); m_menu_ref = menu_ref;
	AppendMenu(parent_menu, m_additional_flags | MF_POPUP, (UINT)menu_handle, m_name);
}

PopUp_Menu::PopUp_Menu(LPCSTR name, UINT additional_flag){
	m_name = name; m_additional_flags = additional_flag;

}
Menu_Item* PopUp_Menu::add_Menu_Item(Menu_Item*m){
	m->callback_create(menu_handle,m_menu_ref);
	return m;
}

Menu::Menu(Windows::ApplicationWindow*aw){
	//aw->addOnMessageInvoke(WM_COMMAND, global_menu_callback);
	ApplicationWindow = aw;
	menu_handle=::CreateMenu();
	ApplicationWindow->addOnMessageInvoke(WM_COMMAND, MENU_IS_MENU_ITEM);//@TODO:schlecht,wegmachen,erste bei release des ganzen,was bei event basiertem Sysmtem wo dann caommands durchflutschen
}

Menu_Item* Menu::add_Menu_Item(Menu_Item*m,HMENU /*m hier ist nicht member//@TODO:umbenennen*/m_menu_handle){
	//Windows::winproc_promise_event wpe = {MENU_IS_MENU_ITEM,WM_COMMAND,false};
	//aus Performance-Gründen onmessageinvoke


	//callbackfunctions.push_back(callbfunc);
	//menu_items_counter++;
	//ApplicationWindow->addOnMessageInvoke(WM_COMMAND, MENU_IS_MENU_ITEM);
	
	m->callback_create(menu_handle,this);
	return m;

}
//@TODO:das hier soll gehn
template <class T_Menu_Class>
T_Menu_Class Menu::add(T_Menu_Class *m){
	m->callback_create(menu_handle,this);
	return m;
}
PopUp_Menu * Menu::add_PopUp_Menu(PopUp_Menu *m){
	m->callback_create(menu_handle, this);
	return m;
}
void Menu::showMenu(){
	::SetMenu(ApplicationWindow->window_handle,menu_handle);

}
unsigned int Menu::get_item_id(Windows::winproc_callback_function callbfunc){
	callbackfunctions.push_back(callbfunc);
	menu_items_counter++;

	return menu_items_counter-1;
}
