#ifndef INC_IMAGE_LOADER_H
#define INC_IMAGE_LOADER_H

//#include <FreeImage.h>
#include "IMGSTRUCTS.h"
class ImageLoader{
	
public:
	ImageLoader();
	~ImageLoader();
	
	/*T_res*/ Image_Load_Result load(const char* filename);
};


#endif