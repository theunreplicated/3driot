#ifndef INC_RESOURCE_LOADING_H
#define INC_RESOURCE_LOADING_H
#include <windows.h>
#include <cstdio>
#include "resource.h"
namespace Resource{
	struct ResourceFileLoadReturnType{
		const char * data=NULL;
		DWORD size = 0;
	};//http://stackoverflow.com/questions/2933295/embed-text-file-in-a-resource-in-a-native-windows-application
	ResourceFileLoadReturnType /***/LoadFileInResource(int name, int type/*, DWORD& size, const char*& data*/)
	{
		HMODULE handle = ::GetModuleHandle(NULL);
		HRSRC rc = ::FindResource(handle, MAKEINTRESOURCE(name),
			MAKEINTRESOURCE(type));
		if (rc == NULL){ throw std::runtime_error("finding resource failed"); }
		HGLOBAL rcData = ::LoadResource(handle, rc);
		if (rcData == NULL){ throw std::runtime_error("getting resource data failed"); }
		ResourceFileLoadReturnType rett;
		rett.size = ::SizeofResource(handle, rc);
		rett.data = static_cast<const char*>(::LockResource(rcData));
		return rett;
	}
	char * CommonLoad(int name, int type){
		ResourceFileLoadReturnType rt=LoadFileInResource(name, type);
		char* buffer = new char[rt.size + 1];
		::memcpy(buffer, rt.data, rt.size);
		buffer[rt.size] = 0; // NULL terminator
		
		return buffer;
	}

};
#endif