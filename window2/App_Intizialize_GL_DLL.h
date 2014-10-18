#pragma once
#include <Windows.h>
class SysUtils_Load_Library;
namespace App_Inizialize_GL_DLL{
	extern SysUtils_Load_Library *dll_opengl;
	PROC __stdcall getProcAddresswglintf(LPCSTR name);


};