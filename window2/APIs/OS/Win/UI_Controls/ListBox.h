#pragma once
#include <Windows.h>
class List_Box_Entry{
	unsigned int m_index; HWND * m_window_handle;
public:
	List_Box_Entry(unsigned int index,HWND * window_handle);
	void remove();
	void insert_before(LPSTR text);
	char* Text_get();
};//@TODO: delete aufrufen irgendwo ,irgendwo muss es ja sein;-)
class List_Box_Entry_representation{
	HWND * window_handle;
public:
	void __List_Box_Entry_representation(HWND*wh);
	List_Box_Entry *operator[](unsigned int index){
		return new List_Box_Entry(index,window_handle);//so nicht korrekt,viele Fehler(fälle) möglich
	};

};
class List_Box_Items{
	HWND * window_handle;
public:
	List_Box_Items(HWND*wh);
	void add(LPSTR text);
	List_Box_Entry_representation entries;
};
class List_Box{
public:
	List_Box(HWND *list_view_handle);
	List_Box_Items*items;

};