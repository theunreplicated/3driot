#pragma once
#include <ft2build.h>
#include FT_FREETYPE_H
//@notice Implemetierung danach http://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Text_Rendering_01
class FreeType_Implementation{
private:
	
	void FT_Function_CHECK(bool result);
	
public:
	FreeType_Implementation();
	FT_Library ft;//@TODO:variablenname unterscheidung ob von freetype oder nur heleper oder external oder sonstwas

};
class FreeType_Face{
	FreeType_Implementation*ft_library;
	FT_Face face;
	void FT_Function_CHECK(FT_Error result);
public:
	void set_font_size(unsigned int height, unsigned int secondparam = 0);
	//http://stackoverflow.com/questions/17348596/freetype-error-ft-load-char-returns-36 daher->folgende Zeile
	
	FT_GlyphSlot load_char(FT_ULong to_load_char, FT_Int32 loadflag = FT_LOAD_RENDER);
	FreeType_Face(FreeType_Implementation*impl, const char*font, unsigned int font_height);
	

};