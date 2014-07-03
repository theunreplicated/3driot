#ifndef INC_FILE_PARSER_H
#define INC_FILE_PARSER_H
#include <string>
#include <vector>
#include "GLStruct_Copy.h"
#include "ImageLoader_Copy.h"
//#include "../window2/ImageLoader.cpp"
//#include "../window2/GLStructs.h"
class FileParser{
private:
	std::string file_contents="";
	
public:
	ImageLoader*img_loader;
	FileParser(std::string file_name);
	std::vector<THREEDObject> parse();
};

#endif