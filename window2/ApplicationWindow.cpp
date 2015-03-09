
#include "ApplicationWindow.h"
#include <Windows.h>
//#include <Uxtheme.h>
//#pragma comment(lib, "uxtheme.lib")
//#define WindowAPIStyle_hacky_WindowRectSplit(wr) wr.x , wr.y ,wr.width,wr.height
namespace Windows{
	std::vector<winproc_callback_function_struct> ApplicationWindow::winproc_callback_function_data;
	std::vector<winproc_additional_data_struct> ApplicationWindow::additional_winproc_data;
	 LRESULT CALLBACK ApplicationWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	
		 for (winproc_callback_function_struct data : winproc_callback_function_data){
			 if (data.message == message){
				 data.cbf(hWnd,wParam,lParam);
				 //return 0;
			 }


		 }
		 for (winproc_additional_data_struct data : additional_winproc_data){



			 if (data.wpe.invoke_on_message == message){
				 bool promise_true_fragezeichen=false; bool called = false;
				 if (data.wpe.use_window_check){
					 if (lParam == (LPARAM)*data.wpe.wnd_ptr){
						 called = true;
						 promise_true_fragezeichen = data.wpe.wpef_callback(hWnd, wParam, lParam, *data.wpe.wnd_ptr);
						 
					 }
				 }



				 else{
					 called=true;//gleich bei jedem callback function des promise event(return true oder false)
					 promise_true_fragezeichen = data.wpe.wpef_callback(hWnd, wParam, lParam, *data.wpe.wnd_ptr);




				 }

				 if (called&&promise_true_fragezeichen){ data.cbf(hWnd, wParam, lParam,*data.wpe.wnd_ptr); }

			 }


		 }
		// return 0;
		switch (message)
		{
		/*case WM_COMMAND:{
			if (::IsDlgButtonChecked(hWnd, 1)) {
				CheckDlgButton(hWnd, 1, BST_UNCHECKED);

			}
			else {
				CheckDlgButton(hWnd, 1, BST_CHECKED);

			}}; break;*/


		case WM_CLOSE:
			PostQuitMessage(0);//schließt alles
			return 0;
		/*case WM_PAINT:{
						  PAINTSTRUCT   ps;
						  HDC           hDC;
						  hDC = BeginPaint(hWnd, &ps);
						  {RECT rect;
						  rect.left = 40;
						  rect.top = 10;
						  const char* message = "My First Window";
						  DrawText(hDC, message, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
						  }
		}break;*/
		case WM_DESTROY:
			return 0;
		

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);

		}



	}//@TODO: abgeleitetete procs von einzelenen controls unterstützen
	 ApplicationWindow::ApplicationWindow(LPCSTR class_name,HINSTANCE hInstance,  WNDPROC proc,wndclass_style_data additonal_style_data)/*:standard_window(window_handle,window_handle)*/{
		 WNDCLASSA wc = {0};
		m_hInstance= hInstance;
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = proc;

		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);//einfach IDC_* ändern
	//	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.hbrBackground =additonal_style_data.background_brush;//win-api.de
		wc.lpszMenuName = NULL;
		wc.lpszClassName = class_name;
	
		(!RegisterClassA(&wc) ?throw std::runtime_error("registering window class failed"):true);
	
		//m_ApplicationWindow = this;//vllt.schlechter stil?
		/*window_handle = CreateWindow(
			names.lpClassName, names.lpWindowName,
			dwStyle,
			rect.x, rect.y, rect.width, rect.height,
			NULL, NULL, hInstance, NULL);
			*/

		//makeAppearBetter(); bringt wohl nichts bei solchen windows
		//::SetWindowTheme(window_handle, L" ", L" ");
	}

	 /*
	 *@warning nicht in message func ausführen
	 */
	 void ApplicationWindow::removeOnMessageInvoke(UINT message, winproc_callback_function callbackf){
		 std::vector<winproc_callback_function_struct>::iterator it = winproc_callback_function_data.begin(); 
		 while (it != winproc_callback_function_data.end())//http://stackoverflow.com/questions/12702561/c-iterate-through-vector-using-for-loop
		 {
			 it++;
			 //http://stackoverflow.com/questions/3779227/why-is-this-vector-iterator-not-incrementable
			 if ((it->message == message) && (it->cbf==callbackf)){
				
			//	it=winproc_callback_function_data.erase(it);
				 winproc_callback_function_data.erase(it);
				break;

			 }
			 //else{ it++; }
		
			 
		 }
		
		
	 }
	void ApplicationWindow::addOnMessageInvoke(UINT message, winproc_callback_function callbackf){
		winproc_callback_function_struct d = {message,callbackf};
		

		winproc_callback_function_data.push_back(d);

	}
}
