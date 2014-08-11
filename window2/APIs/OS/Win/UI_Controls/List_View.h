#pragma once

//#include <iostream>
#include "../../../../Window.h"
#include <CommCtrl.h>
class List_View_Column{
private:
	LVCOLUMN item;
	unsigned int index=0;
	HWND * window_handle;
public:
	List_View_Column(Windows::Window*wh);
	void add(LPSTR text);
	//void remove(){};
	

};

class List_View_Item {
private:
	LVITEM item;
	unsigned int index=0;
	HWND * window_handle;
public:
	List_View_Item(HWND*wh);
	void add(LPSTR text);
	//void remove(){};
	

};


class List_View{
private:
	Windows::Window*m_window_handle;
public:
	List_View(Windows::Window*window_handle);
	List_View_Column *columns;
	List_View_Item *items;
};