#ifndef INC_SysUtils_Load_Library_CPP
#define INC_SysUtils_Load_Library_CPP
#include "SysUtils_Load_Library.h"

template <typename T_Filepath>
SysUtils_Load_Library::SysUtils_Load_Library(T_Filepath file_location){
	lib = LoadLibrary(file_location);
	if (!lib){ throw std::runtime_error(file_location); }
}
template <typename T_Proc_address>
FARPROC __stdcall SysUtils_Load_Library::get_ProcAddress(T_Proc_address proc_address){
	return GetProcAddress(lib, proc_address);
}

template <typename T_import_type, typename T_Proc_address>
T_import_type SysUtils_Load_Library::import(T_Proc_address proc_address){

	return reinterpret_cast<T_import_type>(get_ProcAddress(proc_address));

}
#endif