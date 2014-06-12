#ifndef INC_SysUtils_Load_Library_H/*ich finds besser INC_ davorzuschreiben*/
#define INC_SysUtils_Load_Library_H
#include <Windows.h>
class SysUtils_Load_Library{
public:

	template <typename T_Filepath>
	SysUtils_Load_Library(T_Filepath file_location);
	HMODULE __stdcall lib;
	template <typename T_import_type, typename T_Proc_address>
	T_import_type import(T_Proc_address proc_address);//cast=reinterpret_cast//@TODO:vllt. veränderbar machen,cast auswählbar bei jeder Instanz

	template <typename T_Proc_address>
	FARPROC __stdcall get_ProcAddress(T_Proc_address proc_address);

};
#include "SysUtils_Load_Library.cpp"
#endif