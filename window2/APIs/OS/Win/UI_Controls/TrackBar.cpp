#include "TrackBar.h" //vllt. statt immer so vielen Argumenten structs
#include <CommCtrl.h>
TrackBar::TrackBar(LPCSTR name, Windows::WindowRect rect, Windows::Window*mw, TrackBar_Value_Pairs range_values, TrackBar_Value_Pairs selction_values){
	//http://msdn.microsoft.com/de-de/library/windows/desktop/hh298370(v=vs.85).aspx
	int Menu_id = 5;//@TODO:weg von festem test-wert
	window_handle = new Windows::Window({ TRACKBAR_CLASS, name }, rect,WS_CHILD |
		WS_VISIBLE |
		TBS_AUTOTICKS |
		TBS_ENABLESELRANGE ,mw,NULL,reinterpret_cast<HMENU>(Menu_id));
	SendMessage(window_handle->window_handle, TBM_SETRANGE,
		(WPARAM)TRUE,                   // redraw flag 
		(LPARAM)MAKELONG(range_values.min, range_values.max));  // min. & max. positions

	SendMessage(window_handle->window_handle, TBM_SETPAGESIZE,
		0, (LPARAM)4);                  // new page size 

	SendMessage(window_handle->window_handle, TBM_SETSEL,
		(WPARAM)FALSE,                  // redraw flag 
		(LPARAM)MAKELONG(selction_values.min, selction_values.max));//@cool wäre es wenn hier kein copy n paste

	SendMessage(window_handle->window_handle, TBM_SETPOS,
		(WPARAM)TRUE,                   // redraw flag 
		(LPARAM)selction_values.min);

	SetFocus(window_handle->window_handle);

}