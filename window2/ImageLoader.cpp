#include "ImageLoader.h"
#include <stdexcept>
#include <Windows.h>
#include <FreeImage.h>
#include <IL\il.h>
#include <IL\ilut.h>
ImageLoader::ImageLoader(){
	//FreeImage_Initialise();
	ilutRenderer(ILUT_OPENGL);
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
}
ImageLoader::~ImageLoader(){
	FreeImage_DeInitialise();

}
/*
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
	return{width,height,bits,/*dib,*//*ColorType,iFormat,textura};
}*/
Image_Load_Result ImageLoader::load(const char* filename){
	Image_Load_Result ret;
	//http://r3dux.org/2010/11/single-call-opengl-texture-loader-in-devil/
	ILuint imageID;				// Create an image ID as a ULuint

	GLuint textureID;			// Create a texture ID as a GLuint

	ILboolean success;			// Create a flag to keep track of success/failure

	ILenum error;				// Create a flag to keep track of the IL error state

	ilGenImages(1, &ret.il_image_id); 		// Generate the image ID

	ilBindImage(ret.il_image_id); 			// Bind the image

	success = ilLoadImage(filename); 	// Load the image file

	// If we managed to load the image, then we can start to do things with it...
	if (success)
	{
		// If the image is flipped (i.e. upside-down and mirrored, flip it the right way up!)
		ILinfo ImageInfo;
		iluGetImageInfo(&ImageInfo);
		if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
		{
			iluFlipImage();
		}

		// Convert the image into a suitable format to work with
		// NOTE: If your image contains alpha channel you can replace IL_RGB with IL_RGBA
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		// Quit out if we failed the conversion
		if (!success)
		{
			error = ilGetError();
			throw std::runtime_error("Conversion der Image-Währungen-Euro-Dollar-failed-crash");
			exit(-1);
		}

		// Generate a new texture
		//glGenTextures(1, &textureID);

		// Bind the texture to a name
		//glBindTexture(GL_TEXTURE_2D, textureID);

		// Set texture clamping method
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		// Set texture interpolation method to use linear interpolation (no MIPMAPS)
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		ret.width = ilGetInteger(IL_IMAGE_WIDTH);
		ret.height = ilGetInteger(IL_IMAGE_HEIGHT);
		ret.format = ilGetInteger(IL_IMAGE_FORMAT);
		ret.bits = ilGetData();
		// Specify the texture specification
	/*	glTexImage2D(GL_TEXTURE_2D, 				// Type of texture
			0,				// Pyramid level (for mip-mapping) - 0 is the top level
			ilGetInteger(IL_IMAGE_FORMAT),	// Internal pixel format to use. Can be a generic type like GL_RGB or GL_RGBA, or a sized type
			ilGetInteger(IL_IMAGE_WIDTH),	// Image width
			ilGetInteger(IL_IMAGE_HEIGHT),	// Image height
			0,				// Border width in pixels (can either be 1 or 0)
			ilGetInteger(IL_IMAGE_FORMAT),	// Format of image pixel data
			GL_UNSIGNED_BYTE,		// Image data type
			ilGetData());			// The actual image data itself*/
	}
	else // If we failed to open the image file in the first place...
	{
		error = ilGetError();
		throw std::runtime_error("loading image failed in very hard way");
		exit(-1);
	}

	//ilDeleteImages(1, &imageID); // Because we have already copied image data into texture data we can release memory used by image.

	

	return ret; // Return the GLuint to the texture so you can use it!

}