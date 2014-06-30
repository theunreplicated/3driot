#include "ImageLoader.h"
#include <stdexcept>

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
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))//@TODO:das vllt. wegmachen
		throw std::runtime_error("image loading failed-not a real picuture");



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
	FreeImage_Unload(dib);

	//return success
	return{width,height,bits,dib};
}