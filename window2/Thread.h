#ifndef THREAD_H
#define THREAD_H
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>
typedef struct MyData {
    int val1;
    int val2;
} MYDATA, *PMYDATA;
class Thread{
public:
    HANDLE  hThreadHandle;
    PMYDATA pData;
    DWORD thread_id;
    Thread(LPTHREAD_START_ROUTINE thread_call_func,LPVOID thread_func_arguments);
};

#endif // THREAD_H
