#include "ApplicationWindow.h"
#include "MessageLoop.h"
#include "Window.h"
#include <Windows.h>
#include <stdio.h>
#include "ApplicationUI_Control_Mgr.h"
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
bool CLICK_FUNC(HWND global_wnd, WPARAM wParam, LPARAM lParam, HWND caller_wnd)
{
	
	return /*(lParam == (LPARAM)caller_wnd)&&*/(HIWORD(wParam) == BN_CLICKED);
	
	
}
void winproc_callback_function5(HWND hWnd, WPARAM wParam, LPARAM lParam){
	//MessageBox(NULL, "dd","cc", MB_OK);
	PAINTSTRUCT   ps;
	HDC           hDC;
	hDC = BeginPaint(hWnd, &ps);
	{RECT rect;
	rect.left = 40;
	rect.top = 10;
	const char* message = "My First Window";
	DrawText(hDC, message, -1, &rect, DT_SINGLELINE | DT_NOCLIP); }
}

void onclick(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

	MessageBox(NULL,"fd","ds",MB_OK);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int iCmdShow)
{
	using namespace Windows;
	int width=1024, height=768;
	ApplicationWindow*aw = new ApplicationWindow(hInstance, { "t1", "t2" }, { width, height }, WS_VISIBLE | WS_OVERLAPPEDWINDOW);
	//Window*wedit = new Window(hInstance, { "edit", "freetext" }, { 155, 155 }, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE |ES_AUTOVSCROLL, aw);
	//Window*wbtn = new Window(hInstance, { "button", "button" }, { 555, 555,200,200 }, WS_CHILD | WS_VISIBLE, aw);
	//aw->addOnMessageInvoke(WM_MOUSEMOVE,winproc_callback_function5);//WM_CREATE shafft er net
	aw->addOnMessageInvoke(WM_PAINT,winproc_callback_function5);
	//MessageBox(NULL, wedit->Text_get(), wedit->Text_get(), MB_OK);

	winproc_promise_event BTN_CLICK = {CLICK_FUNC, WM_COMMAND, true /*default=false*/};
	//wbtn->on(BTN_CLICK,onclick);
	
	//erstelle controls am rechten Rand

	aw->show();
	ApplicationUI_Control_Mgr*uicontrol = new ApplicationUI_Control_Mgr(aw,width,height);
	uicontrol->addEditControls();
	uicontrol->addButtons(BTN_CLICK);
	//cc(aw);
	//cc*dd = new cc(aw);
//	dd->ccs();


	//new Window(hInstance, { "button", "Neue Reihe hinzufügen" }, { 175, 30, edit_startpoint_w - ((editwidth + padding_w) * 1), edit_startpoint_h+50 }, WS_CHILD | WS_VISIBLE, aw);
	//new Window(hInstance, { "edit", "x" }, { editwidth, editheight, edit_startpoint_w, edit_startpoint_h+padding }, WS_CHILD | WS_VISIBLE, aw);




		(new MessageLoop())->GetMessage_Approach();
}