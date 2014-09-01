#include "TreeView.h"
#include <stdexcept>
Tree_View_Items::Tree_View_Items(HWND wh, HTREEITEM parent_item){
	window_handle = wh;
	parent = parent_item;


}
Tree_View_Items * Tree_View_Items::add(LPSTR text, Tree_View_Items * insert_after_item){
	TVITEM tvi;
	TVINSERTSTRUCT tvins;
	HTREEITEM hItem;

	tvi.mask = TVIF_TEXT;
	tvi.pszText = text;
	tvi.cchTextMax = lstrlen(text);

	// die Insert-Struktur wird vorbereitet 
	tvins.item = tvi;
	//if (item_insert_after) {
	//	tvins.hInsertAfter = item_insert_after;
	//}
	//else {
	//	tvins.hInsertAfter = TVI_FIRST;
	//}
	if (insert_after_item!=nullptr){
		tvins.hInsertAfter = insert_after_item->parent;
	}
	
	tvins.hParent = parent;

	// Nachricht zum Einbinden an das Kontrollelement versenden 
	hItem = reinterpret_cast<HTREEITEM>(SendMessage(window_handle, TVM_INSERTITEM, NULL, (LPARAM)&tvins));
	if (!hItem)
	{
		throw std::runtime_error("fail treeview creation");
	}
	return new Tree_View_Items(window_handle,hItem);
	
}

Tree_View::Tree_View(HWND wh){

	window_handle=wh;
	items = new Tree_View_Items(wh,TVI_ROOT);
}
HTREEITEM Tree_View::AddItemToTree( LPSTR lpszItem, HTREEITEM parent
	, HTREEITEM item_insert_after//http://www.willemer.de/informatik/windows/wintree.htm#top
	){//http://www.c-plusplus.de/forum/264422-full
	TVITEM tvi;
	TVINSERTSTRUCT tvins;
	HTREEITEM hItem;

	tvi.mask = TVIF_TEXT;
	tvi.pszText = lpszItem;
	tvi.cchTextMax = lstrlen(lpszItem);

	// die Insert-Struktur wird vorbereitet 
	tvins.item = tvi;
	if (item_insert_after) {
		tvins.hInsertAfter = item_insert_after;
	}
	else {
		tvins.hInsertAfter = TVI_FIRST;
	}
	if (parent == 0) {
		tvins.hParent = TVI_ROOT;
	}
	else {
		tvins.hParent = parent;
	}

	// Nachricht zum Einbinden an das Kontrollelement versenden 
	hItem = reinterpret_cast<HTREEITEM>(SendMessage(window_handle, TVM_INSERTITEM, NULL, (LPARAM)&tvins));
	if (!hItem)
	{
		throw std::runtime_error("fail treeview creation");
	}
	return hItem;
}