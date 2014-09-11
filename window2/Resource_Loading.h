#ifndef INC_RESOURCE_LOADING_H
#define INC_RESOURCE_LOADING_H
//#include <windows.h>
//#include <cstdio>
//#include "resource.h"
struct ResourceFileLoadReturnType;
namespace Resource{
	ResourceFileLoadReturnType* /***/LoadFileInResource(int name, int type/*, DWORD& size, const char*& data*/);
	char * CommonLoad(int name, int type);
};
#endif