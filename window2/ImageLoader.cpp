#include "ImageLoader.h"
#include <stdexcept>
#include <Windows.h>
#include <FreeImage.h>
ImageLoader::ImageLoader(){
	FreeImage_Initialise();

}
ImageLoader::~ImageLoader(){
	FreeImage_DeInitialise();

}

Image_Load_Result ImageLoader::load(const char* filename){
	//Quelle:offizielles Beispiel opengl
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	//GLuint gl_texID;

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		throw std::runtime_error("image loading failed-unknown File Type");

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		throw std::runtime_error("image loading failed-loading process failed in a very mysterious way,mhhh....");

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	FIBITMAP* imagen = FreeImage_ConvertTo32Bits(dib);

	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))//@TODO:das vllt. wegmachen
		throw std::runtime_error("image loading failed-not a real picuture");

	
	ColorData ColorType;
	switch (FreeImage_GetColorType(dib))
	{
	case FIC_RGB:
		ColorType = ColorData_RGB;
		//this->channels = 3;
		break;
	case FIC_RGBALPHA:
		ColorType = ColorData_RGB;
		//this->channels = 4;
		break;
	default:
		ColorType = ColorData_RGB;
		//return false;
	}
	
	//Code auch z.t von hier :http://stackoverflow.com/questions/19606736/loading-an-image-with-freeimage

	FreeImage_Unload(dib);
	unsigned char * textura = new unsigned char[4 * width*height];
	char* pixeles = (char*)FreeImage_GetBits(imagen);

	for (int j = 0; j<width*height; j++)
	{
		textura[j * 4 + 0] = pixeles[j * 4 + 2];
		textura[j * 4 + 1] = pixeles[j * 4 + 1];
		textura[j * 4 + 2] = pixeles[j * 4 + 0];
		textura[j * 4 + 3] = pixeles[j * 4 + 3];
	}

	//generate an OpenGL texture ID for this texture
	//glGenTextures(1, &gl_texID);
	//store the texture ID mapping
	//m_texID[texID] = gl_texID;
	//bind to the new texture ID
	//glBindTexture(GL_TEXTURE_2D, gl_texID);
	//store the texture data for OpenGL use
	//glTexImage2D(GL_TEXTURE_2D, level, internal_format, width, height,
		//border, image_format, GL_UNSIGNED_BYTE, bits);

	//Free FreeImage's copy of the data
	//FreeImage_Unload(dib);
	
	//int*testvar= new int;
	//testvar[0] = 512;
//	unsigned int iBPP = FreeImage_GetBPP(dib);
	//int GL_BGR = 0x80E0;
	//int GL_LUMINANCE = 0x1909;
	//int iFormat = iBPP == 24 ? GL_BGR : iBPP == 8 ? GL_LUMINANCE : 0;
	int iFormat = 0;//@TODO:das wegmachen,ist nur n dummy
	//return success
	return{width,height,bits,dib,ColorType,iFormat,textura};
}