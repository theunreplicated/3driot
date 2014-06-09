#include "MessageLoop.h"
#include <Windows.h>
namespace Windows{
	int MessageLoop::GetMessage_Approach(){
		MSG Msg;//meanwhile...statt while
		while (GetMessage(&Msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		return Msg.wParam;
	}
}