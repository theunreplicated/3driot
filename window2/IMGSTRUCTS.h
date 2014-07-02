#ifndef IMG_STRUCT_H
#define IMG_STRUCT_H
enum ColorData{ ColorData_RGB, ColorData_RGBA, ColorData_UNDEFINED };
struct FI2BITMAP { void *data; };
struct Image_Load_Result{
	/*unsigned*/int width, height;
	unsigned char*bits;
	//FI2BITMAP *dib;//@note: dib ist ein interner Pointer,muss nach glTexImage(Sprich:Laden auf die Grafikkarte) mit FreeImage_Unload(dib) released(nicht das Release) werden
	ColorData color_type;
	int format;
	unsigned char*texture_bytes;
	//void unload(){ FreeImage_Unload(dib); };

};
struct image_stor :Image_Load_Result{
	const char* texture_name;

};
#endif