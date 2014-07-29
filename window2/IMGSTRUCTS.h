#ifndef IMG_STRUCT_H
#define IMG_STRUCT_H
//#include <IL\il.h>
//#include <IL\ilut.h>
#include <string>
enum ColorData{ ColorData_RGB, ColorData_RGBA, ColorData_UNDEFINED };
struct FI2BITMAP { void *data; };
struct Image_Load_Result{
	/*unsigned*/int width, height;
	unsigned char*bits;
	//FI2BITMAP *dib;//@note: dib ist ein interner Pointer,muss nach glTexImage(Sprich:Laden auf die Grafikkarte) mit FreeImage_Unload(dib) released(nicht das Release) werden
	ColorData color_type;
	int format;
	//unsigned char*texture_bytes;
	//void unload(){ ilDeleteImages(1, &il_image_id); };
	unsigned int il_image_id;
	std::string file_path,file_name;
	
};
struct image_stor :Image_Load_Result{
	/*const char**/std::string texture_name;//@note:ganz böser Fehler,hatte vergessen dass Pointer ist,am besten ist dann immer string,trotz Performancenachteil
	
	bool operation_failed = false;
	unsigned int global_texture_id;//Bugs vom VC_Compiler:schwerwiegend:zuerst first-chance exception access error;dannn noch alter name gespeichert
};
#endif