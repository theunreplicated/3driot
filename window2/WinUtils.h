#ifndef INC_WIN_UTILS_H
#define INC_WIN_UTILS_H
#include <Windows.h>
#include <string>
class Win_Utils{
public:
	std::string getdirpath(WCHAR* chr);
	bool saveToFile(const char* fileName, const char * data);
};

#endif