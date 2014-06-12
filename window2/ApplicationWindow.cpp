
#include "ApplicationWindow.h"
#include <Windows.h>


namespace Windows{
	std::vector<winproc_callback_function_struct> ApplicationWindow::winproc_callback_function_data;
	std::vector<winproc_additional_data_struct> ApplicationWindow::additional_winproc_data;
	 LRESULT CALLBACK ApplicationWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
		 
		 for (winproc_callback_function_struct data : winproc_callback_function_data){
			 if (data.message == message){
				 data.cbf(hWnd,wParam,lParam);

			 }


		 }
		 for (winproc_additional_data_struct data : additional_winproc_data){



			 if (data.wpe.invoke_on_message == message){
				 bool promise_true_fragezeichen; bool called = false;
				 if (data.wpe.use_window_check){
					 if (lParam == (LPARAM)*data.wpe.wnd_ptr){
						 called = true;
						 promise_true_fragezeichen = data.wpe.wpef_callback(hWnd, wParam, lParam, *data.wpe.wnd_ptr);
					 }
				 }



				 else{
					 called=true;
					 promise_true_fragezeichen = data.wpe.wpef_callback(hWnd, wParam, lParam, *data.wpe.wnd_ptr);




				 }

				 if (called&&promise_true_fragezeichen){ data.cbf(hWnd, wParam, lParam); }

			 }


		 }
		
		switch (message)
		{

		case WM_CREATE:

			return 0;

		case WM_CLOSE:
			PostQuitMessage(0);
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
		case WM_SIZE:
			//glm->render();
			break;
		case WM_KEYDOWN:
			switch (wParam)
			{

			case VK_ESCAPE:
				PostQuitMessage(0);
				return 0;

			}
			return 0;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);

		}



	}
	ApplicationWindow::ApplicationWindow(HINSTANCE hInstance, WindowNames<LPCSTR> names, WindowRect rect, DWORD dwStyle):standard_window(&native_window_handle,&native_window_handle){
		WNDCLASS wc;
		m_hInstance= hInstance;
		// register window class
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);//einfach IDC_* �ndern
	//	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;//win-api.de
		wc.lpszMenuName = NULL;
		wc.lpszClassName = names.lpClassName;
		RegisterClass(&wc);

		native_window_handle = CreateWindow(
			names.lpClassName, names.lpWindowName,
			dwStyle,
			rect.x, rect.y, rect.width, rect.height,
			NULL, NULL, hInstance, NULL);

	}
	void ApplicationWindow::addOnMessageInvoke(UINT message, winproc_callback_function callbackf){
		winproc_callback_function_struct d = {message,callbackf};
		

		winproc_callback_function_data.push_back(d);

	}
}
