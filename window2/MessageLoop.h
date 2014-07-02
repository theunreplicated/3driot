#ifndef MESSAGE_LOOP_H
#define MESSAGE_LOOP__H
#include <Windows.h>
namespace Windows{
	class MessageLoop{
	
		
	public:MSG Msg;
		int GetMessage_Approach();
		bool Message_Get();
		void Message_Pump();
		int Message_Pump_End();

	
	};

}
#endif