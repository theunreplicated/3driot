#include "List_View.h"
#include <Windows.h>
List_View::List_View(Windows::Window*window_handle)/*da oben kommt jetzt nix hin,keine lust mehr*/{
	//@TODO:angucken http://stackoverflow.com/questions/12796501/detect-clicking-inside-listview-and-show-context-menu
	m_window_handle = window_handle;
	columns = new List_View_Column(window_handle);
	items = new List_View_Item(&window_handle->window_handle);
}
//Variablen daher,da ich es ursprünglich als Template-Klasse gamcht habe
List_View_Column::List_View_Column(Windows::Window*wh){ 
	window_handle = &(wh->window_handle);
	item.mask = LVCF_TEXT | LVCF_WIDTH;
	item.cx = wh->Position_get().width/*eigentlich eher unnötig*/;
}
void List_View_Column::add(LPSTR text){ item.pszText = text; ListView_InsertColumn(*window_handle, index, &item); index++; };
List_View_Item::List_View_Item(HWND*wh){
	window_handle = wh; item.mask = LVIF_TEXT; item.iSubItem = 0;
};
void List_View_Item::add(LPSTR text){ item.pszText = text; item.iItem = index; ListView_InsertItem(*window_handle, &item); index++; };

/*LVCOLUMN lvc;
//lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
lvc.iSubItem = 0;
lvc.pszText = "Tdsdsadsitle";
lvc.cx = 50;
lvc.fmt = LVCFMT_LEFT;
ListView_InsertColumn(list, 0, &lvc);
http://stackoverflow.com/questions/11923925/disable-horizontal-scroll-bar-in-list-view @TODO:implement
//http://www.cplusplus.com/forum/windows/47702/
//http://stackoverflow.com/questions/3217362/adding-items-to-a-listview
*/

//http://stackoverflow.com/questions/11923925/disable-horizontal-scroll-bar-in-list-view
/*LONG lStyle = GetWindowLong(list, GWL_STYLE);
lStyle |=WS_VSCROLL;
lStyle |= WS_HSCROLL;
SetWindowLong(list, GWL_STYLE, lStyle);
*/
/*LVCOLUMN lvc;

lvc.mask = LVCF_TEXT | LVCF_WIDTH;
lvc.cx = lwidth;
lvc.pszText = TEXT("Property");
ListView_InsertColumn(list, 0, &lvc);

//lvc.cx = 500;
//lvc.pszText = TEXT("Value");
//ListView_InsertColumn(list, 1, &lvc);

LVITEM lvi;

lvi.mask = LVIF_TEXT;
//lvi.iItem = 1;
lvi.iSubItem = 0;
//lvi.pszText = TEXT("File Name");
//ListView_InsertItem(list, &lvi);
//lvi.iItem = 1;
lvi.pszText = "File Size";
ListView_InsertItem(list, &lvi);
for (int i = 0; i < 100; i++){
lvi.iItem = i;
ListView_InsertItem(list, &lvi);
}

*/

//ListView_SetItemText(list, 0, 1, TEXT("123425244525"));*/
