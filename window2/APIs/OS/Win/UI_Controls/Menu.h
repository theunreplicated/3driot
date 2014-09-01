#pragma once
//@TODO:gucken warum das &(ampersand) bei Appendmenu
#include "../../../ApplicationWindow.h"
#include <vector>
class Menu;
class Menu_Item{
	LPCSTR m_name; UINT m_additional_flags; Menu*menu_ref; Windows::winproc_callback_function m_callbfunc;
public:
	
	Menu_Item(LPCSTR name, Windows::winproc_callback_function callbfunc, UINT additional_flag = MF_STRING);
	void callback_create(HMENU parent_menu, Menu*menu_ref);
};//am besten wären meherer möglichkeiten zum intialisiern/binden automatisch generiert,z.b. bei Menu->add() anders als direkt add (hab keinen    Lust auf diesen Kommentar)

class PopUp_Menu{
	LPCSTR m_name; UINT m_additional_flags; Menu*m_menu_ref; 
public:
	HMENU menu_handle;//friend --mein bester Freund
	PopUp_Menu(LPCSTR name, UINT additional_flag= MF_STRING);
	void callback_create(HMENU parent_menu,Menu*menu_ref);
	Menu_Item* add_Menu_Item(Menu_Item*m);
};
class Menu{
private:
	HMENU menu_handle;
	static std::vector<Windows::winproc_callback_function> callbackfunctions;
	Windows::ApplicationWindow* ApplicationWindow;
	static unsigned int menu_items_counter/*und damit die globale WM_COMMAnd loword param,also sonst kein Elemnt darf in diesem Wertebereich so sein*/;
public:
	static void MENU_IS_MENU_ITEM(HWND hWnd, WPARAM wParam, LPARAM lParam);/*@TODO:private*/
	Menu(Windows::ApplicationWindow* aw);
	template <class T_Menu_Class>
	T_Menu_Class add(T_Menu_Class *m);
	Menu_Item* add_Menu_Item(Menu_Item*m, HMENU m_menu_handle=NULL);
	PopUp_Menu * add_PopUp_Menu(PopUp_Menu *m);
	void showMenu();
	unsigned int get_item_id(Windows::winproc_callback_function callbfunc);
};
