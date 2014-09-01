#pragma once
#include <Windows.h>
class Combo_Box_Entry{
	unsigned int m_index; HWND * m_window_handle;
public:
	Combo_Box_Entry(unsigned int index,HWND*window_handle);
	void remove();
	void Text_replace(LPSTR text);
	char* Text_get();
	void insert_before(LPSTR text);
};
class Combo_Box_Entry_representation{
	HWND * window_handle;
public:
	void __Combo_Box_Entry_representation(HWND*wh);
	Combo_Box_Entry *operator[](unsigned int index){
		return new Combo_Box_Entry(index, window_handle);//so nicht korrekt,viele Fehler(fälle) möglich
	};
};//@TODO:das ganze copy n paste hier mergen

class Combo_Box_Items{
	HWND * window_handle;
public:
	Combo_Box_Items(HWND *wh);
	void add(LPSTR text);
	Combo_Box_Entry_representation entries;
};
class Combo_Box{
	HWND * window_handle;
public:
	Combo_Box(HWND * combo_box_handle);
	Combo_Box_Items*items;
};