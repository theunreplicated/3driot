#include "../window2/SysUtils_Load_Library.h"
namespace App_Inizialize_GL_DLL{
	SysUtils_Load_Library *dll_opengl;
	PROC __stdcall getProcAddresswglintf(LPCSTR name){

		return dll_opengl->get_ProcAddress(name);
	};

};