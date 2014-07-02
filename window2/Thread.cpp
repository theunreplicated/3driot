#include "Thread.h"
#include <stdexcept>
//http://msdn.microsoft.com/en-us/library/windows/desktop/ms682516%28v=vs.85%29.aspx
Thread::Thread(LPTHREAD_START_ROUTINE thread_call_func,LPVOID thread_func_arguments){
    pData= (PMYDATA) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                   sizeof(MYDATA));

           if( pData == NULL )
           {
              // If the array allocation fails, the system is out of memory
              // so there is no point in trying to print an error message.
              // Just terminate execution.
               ExitProcess(2);
           }

    hThreadHandle=CreateThread(
                NULL,                   // default security attributes
                0,                      // use default stack size
               thread_call_func,       // thread function name
                thread_func_arguments,          // argument to thread function
                0,                      // use default creation flags
                &thread_id);
    if (hThreadHandle == NULL)
            {
               //ErrorHandler(TEXT("CreateThread"));
        throw new std::runtime_error("Thread creation failed");
               ExitProcess(3);
            }


}
