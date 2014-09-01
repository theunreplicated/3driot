#include "CheckBox.h"
//einheitliche regeln ob pointer name,code wird z.t. automatisch generiert,ich mache nur vorgaben,das wäre cool
//oder auch automatisch call anhand template typename ob unicode oder ansi funktion
//kein Subclassing möglich
//WM_COMMAND and WM_NOTIFY werden wohl immer ans parent window geschickt
//@TODO:subclassing mit callwndproc(parent,...)
void  btn_callback(HWND hWnd, WPARAM wParam, LPARAM lParam){

	if (::IsDlgButtonChecked(hWnd, 1)) {
		CheckDlgButton(hWnd, 1, BST_UNCHECKED);

	}
	else {
		CheckDlgButton(hWnd, 1, BST_CHECKED);
		//1=id@TODO:global,für verschiedene ids,nicht in KOnflikte mit Menu kommen
	}
}
CheckBox::CheckBox(LPCSTR text,Windows::WindowRect rect,Windows::ApplicationWindow*aw,DWORD additional_styles){
window = new Windows::Window({ "BUTTON", text}, rect, additional_styles | WS_CHILD | /*BS_AUTOCHECKBOX*/BS_CHECKBOX,aw,NULL,NULL,reinterpret_cast<HMENU>(1));
//@TODO:gucken warum normale checkbox nicht geht,komischerweise nicht in diesem projekt ,jedoch im separatem
aw->addOnMessageInvoke(WM_COMMAND, btn_callback);//@TODO:darf nur 1x prop orc aufgerufen werden//@TODO:register in applicationwindow//qTODO:Fix:falls filedialog,dann geht das häkchen weg
ApplicationWindow = aw;
}
void CheckBox::check(){
	::CheckDlgButton(ApplicationWindow->window_handle, 1, BST_CHECKED);
	//komplett falsch:checkdlgbutton auf parent
}
void CheckBox::uncheck(){
	::CheckDlgButton(ApplicationWindow->window_handle, 1, BST_UNCHECKED);

}
bool CheckBox::is_checked(){
	return ::IsDlgButtonChecked(ApplicationWindow->window_handle, 1);

}
bool CheckBox::EVENT_IS_CHECKED(HWND global_wnd, WPARAM wParam, LPARAM lParam, HWND caller_wnd){
	bool checked=::IsDlgButtonChecked(global_wnd, 1);
	::CheckDlgButton(global_wnd, 1, BST_CHECKED);
	return true;
}