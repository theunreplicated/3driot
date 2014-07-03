#ifndef IMAGE_LOADER_COPY_H
#define IMAGE_LOADER_COPY_H
#include "GLStruct_Copy.h"
class ImageLoader{
public:
	ImageLoader();
	~ImageLoader(); 
	image_stor load(const char* filename);
};


#endif