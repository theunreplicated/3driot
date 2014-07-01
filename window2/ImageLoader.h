#ifndef INC_IMAGE_LOADER_H
#define INC_IMAGE_LOADER_H

#include <FreeImage.h>
enum ColorData{ ColorData_RGB, ColorData_RGBA, ColorData_UNDEFINED };
struct Image_Load_Result{
	/*unsigned*/int width, height;
	unsigned char*bits;
	FIBITMAP *dib;//@note: dib ist ein interner Pointer,muss nach glTexImage(Sprich:Laden auf die Grafikkarte) mit FreeImage_Unload(dib) released(nicht das Release) werden
	ColorData color_type; 
	int format;
	unsigned char*texture_bytes;
	//void unload(){ FreeImage_Unload(dib); };

};
class ImageLoader{
	
public:
	ImageLoader();
	~ImageLoader();
	Image_Load_Result load(const char* filename);
};


#endif