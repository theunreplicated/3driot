#ifndef INC_THREAD_H
#define INC_THREAD_H
#include <Windows.h>
//typedef void(__cdecl*Thread_Begin_Function)(void*);
typedef DWORD(__stdcall*Thread_Begin_Function)(void*);


namespace Threading{
	void register_thread_message_loop();
	extern inline bool message_get(MSG & msg);
	HANDLE event_create();
}
class Thread{
public:
	unsigned int thread_id;
	HANDLE thread_handle=NULL;
	Thread(Thread_Begin_Function bgf);




};
#endif