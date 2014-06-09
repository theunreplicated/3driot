#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H
#include <Windows.h>
#include <vector>
#include "WindowStructs.h"
namespace Windows{
	
	struct winproc_callback_function_struct{
		UINT message;
		winproc_callback_function cbf;
	};
	struct winproc_addittional_callbackf_input_data_extended{
		HWND on_invoke_window;
		winproc_callback_function callbackf;

	};
	struct winproc_addittional_callbackf_input_data{
		std::vector<winproc_addittional_callbackf_input_data_extended>window_handles;
		UINT message;//on invoke
	};
	

	
	class ApplicationWindow{
	//private:
	//public://TODO:Friend calss
		
	public:
		HINSTANCE m_hInstance;
		ApplicationWindow(HINSTANCE hInstance, WindowNames<LPCSTR> names, WindowRect rect, DWORD dwStyle);
		HWND native_window_handle;
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		void addOnMessageInvoke(UINT message, winproc_callback_function callbackf);
		static std::vector<winproc_additional_data_struct> additional_winproc_data;
		static std::vector<winproc_callback_function_struct> winproc_callback_function_data;
	};
}

#endif