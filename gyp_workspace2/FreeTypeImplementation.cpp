#include "FreeTypeImplementation.h"
#include <stdexcept>

void FreeType_Implementation::FT_Function_CHECK(bool result){//@TODO:das mit bool ist net so optimal hier
	
	if (result){ throw std::runtime_error("freetype impl returned an error"); }//@TODO: eigene error klassen,1. ebene freetpye klassen,2.ebene freetype darunter


}
FreeType_Implementation::FreeType_Implementation(){//standardisierte reihenfolge,z.b. zuerst konstruktur,dann private usw. wären gut,struktur,struktur,struktur(also auch so dass de pc damit was anfangen kann)

	FT_Function_CHECK(FT_Init_FreeType(&ft));

}

void FreeType_Face::FT_Function_CHECK(FT_Error result){
	
	if (result!=0){ throw std::runtime_error("freetype face returned an error"); }
}
FreeType_Face::FreeType_Face(FreeType_Implementation*impl,const char*font){
	ft_library = impl;//@TODO:pointer check
	FT_Function_CHECK(FT_New_Face(impl->ft, font, 0, &face));


}
void FreeType_Face::set_font_size(unsigned int height, unsigned int secondparam){
	//@TODO:rules groß und kleinschreibung
	FT_Function_CHECK(FT_Set_Pixel_Sizes(face, secondparam, height));
}
FT_GlyphSlot FreeType_Face::load_char(FT_ULong to_load_char,FT_Int32 loadflag){
	FT_Function_CHECK(FT_Load_Char(face, to_load_char, loadflag));//ruft internf ft_load_glyph auf,also highe rlevel da nich anzahl
	return face->glyph;
}