#include "ComboBox.h"
#include <stdexcept>
//http://msdn.microsoft.com/en-us/library/windows/desktop/hh298364(v=vs.85).aspx
//@TODO: bei user selection
Combo_Box::Combo_Box(HWND * combo_box_handle){
	window_handle = combo_box_handle;//fehler bei der varialbnebenennung,sorry
	items = new Combo_Box_Items(combo_box_handle);
}
Combo_Box_Items::Combo_Box_Items(HWND *wh){

	window_handle = wh;
	entries.__Combo_Box_Entry_representation(wh);
}
void Combo_Box_Items::add(LPSTR text){

	::SendMessage(*window_handle, CB_ADDSTRING, NULL, reinterpret_cast<LPARAM>(text));
}
void Combo_Box_Entry_representation::__Combo_Box_Entry_representation(HWND *wh){
	window_handle = wh;

}
Combo_Box_Entry::Combo_Box_Entry(unsigned int index, HWND*window_handle){
	m_index = index;
	m_window_handle = window_handle;
}
void Combo_Box_Entry::remove(){
	SendMessage(*m_window_handle, CB_DELETESTRING, m_index, NULL);


}
void Combo_Box_Entry::Text_replace(LPSTR text){
	
	::SendMessage(*m_window_handle, CB_SETITEMDATA, m_index, reinterpret_cast<LPARAM>(text));
	throw std::runtime_error("you should nout use this funcion sbecause it's broken and is not working therefore");

}
char* Combo_Box_Entry::Text_get(){//@TODO:char durch tchar ersetzten
	unsigned int len = ::SendMessage(*m_window_handle, CB_GETLBTEXTLEN, m_index, NULL);
	char* buffer = new char[len + 1];//+1 wohl wegen dem \0 Schlusszeichen-bin mir baer nicht sicher ob hier nötig@TODO:checken@TODO:nachher vereinheitlichen bei winapi
	::SendMessage(*m_window_handle, CB_GETLBTEXT, m_index, reinterpret_cast<LPARAM>(buffer));
	return buffer;
	//@TODO:testen
}
void Combo_Box_Entry::insert_before(LPSTR text){

	::SendMessage(*m_window_handle, CB_INSERTSTRING, m_index, reinterpret_cast<LPARAM>(text));
}