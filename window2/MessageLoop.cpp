#include "MessageLoop.h"
#include <Windows.h>
namespace Windows{
	int MessageLoop::GetMessage_Approach(){
		//MSG Msg;//meanwhile...statt while
		while (Message_Get())
		{
			Message_Pump();
		}
		return Message_Pump_End();
	}
	bool MessageLoop::Message_Get(){

		return ::GetMessage(&Msg, NULL, 0, 0) > 0;
	}
	void MessageLoop::Message_Pump(){
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);

	}
	int MessageLoop::Message_Pump_End(){

		return Msg.wParam;
	}
}