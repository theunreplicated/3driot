#include "Thread.h"
//#include <process.h>
//#include "include\base\cef_logging.h"
//typedef void(__cdecl*Tccx)(void hallo);
namespace Threading{
	
	HANDLE event_create(){
		return CreateEvent(NULL, FALSE, FALSE, NULL);		
	}
	void register_thread_message_loop(){
		::PostThreadMessage(::GetCurrentThreadId(), WM_USER+1/*bin mir nicht sicher mit nur WM_USER,auch WM_USER+1 möglich*/, 0, 0);
	}
	inline bool message_get(MSG & msg){

		return ::GetMessage(&msg, NULL, 0, 0);
	}
}

Thread::Thread(Thread_Begin_Function bgf){
//auto thread_handle=_beginthreadex(NULL, 0, ThreadFunc, NULL, 0, NULL);
	//auto th=_beginthread(bgf, 0, NULL);
//	auto th = _beginthreadex(NULL, 0,bgf,NULL,0,&thread_id);
	auto th = ::CreateThread(NULL, 0, bgf, NULL, 0, reinterpret_cast<LPDWORD>(&thread_id));
//CHECK(th);//unterschied zu beginthread  http://stackoverflow.com/questions/331536/windows-threading-beginthread-vs-beginthreadex-vs-createthread-c

thread_handle = reinterpret_cast<HANDLE>(th);
}
