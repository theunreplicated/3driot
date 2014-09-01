#include <Windows.h>
#include <CommCtrl.h>
class Tree_View_Items{
	HWND window_handle;
	
public:
	HTREEITEM parent;
	Tree_View_Items(HWND wh, HTREEITEM parent_item);
	Tree_View_Items * add(LPSTR text, Tree_View_Items * insert_after_item=nullptr);
//	Tree_View_Items*operator[](unsigned int index){
		//return new Tree_View_Items(window_handle, index);
	//};
};
class Tree_View{
	HWND window_handle;
public:
	Tree_View(HWND wh); 
	HTREEITEM AddItemToTree(LPSTR lpszItem, HTREEITEM parent, HTREEITEM item_insert_after);
	Tree_View_Items* items;
};