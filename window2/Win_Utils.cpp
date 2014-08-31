#include "WinUtils.h"
#include <fstream>
std::string Win_Utils::getdirpath(WCHAR *chr){
	int len = wcslen(chr); int lastlength; int last = len - 1;

	//chr+=(len-1);
	//for(int i=0;i<=len;i++){
	//if(strstr(chr,"\\")==NULL){break;}else{
	//lastlength=strlen(chr);
	//qDebug()<<"--"<<chr<<lastlength;chr++;};

	//}
	WCHAR * l = L"\\";

	while (chr[last] != *l){
		last--;
	}
	//delete l;
	//last ist letztes Element,von 0 bis dahin brauchen wir die Strings


	//buffer[0]=l[0];
	//buffer=
	std::string buffer;
	for (int i = 0; i<last/*extra -1*/; i++){
		buffer += chr[i];

	}

	return buffer;

}
WCHAR *Win_Utils::getExePath(){
	HMODULE hModule = GetModuleHandleW(NULL);
	WCHAR  *path= new WCHAR[MAX_PATH];
	GetModuleFileNameW(hModule, path, MAX_PATH);//path von exe//da assimp wohl den include path auf desktop setzt irgendwie?
	return path;
}
bool Win_Utils::saveToFile(const char* fileName, const char * data){
	std::ofstream fs;
	fs.open(fileName, std::ios::out | std::ios::trunc);

	fs << data;
	fs.close();

	return true;
}