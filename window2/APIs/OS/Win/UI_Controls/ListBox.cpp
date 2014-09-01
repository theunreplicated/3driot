#include "ListBox.h"
List_Box::List_Box(HWND *list_view_handle){
	items = new List_Box_Items(list_view_handle);

}
List_Box_Items::List_Box_Items(HWND *wh){
	window_handle = wh;
	entries.__List_Box_Entry_representation(wh);
}
void List_Box_Items::add(LPSTR text){

	SendMessage(*window_handle, LB_ADDSTRING,NULL, reinterpret_cast<LPARAM>(text));
}
void List_Box_Entry_representation::__List_Box_Entry_representation(HWND*wh){
	window_handle = wh;


}
List_Box_Entry::List_Box_Entry(unsigned int index, HWND * window_handle){

	m_index = index; m_window_handle = window_handle;
}
void List_Box_Entry::remove(){
	::SendMessage(*m_window_handle, LB_DELETESTRING, m_index, NULL);

}
void List_Box_Entry::insert_before(LPSTR text){

	::SendMessage(*m_window_handle, LB_INSERTSTRING, m_index, reinterpret_cast<LPARAM>(text));
}
char* List_Box_Entry::Text_get(){
	unsigned int len=::SendMessage(*m_window_handle, LB_GETTEXTLEN, m_index, NULL);
	char* buffer = new char[len + 1];//+1 wohl wegen dem \0 Schlusszeichen-bin mir baer nicht sicher ob hier nötig@TODO:checken@TODO:nachher vereinheitlichen bei winapi
	::SendMessage(*m_window_handle, LB_GETTEXT, m_index, reinterpret_cast<LPARAM>(buffer));
	return buffer;
}