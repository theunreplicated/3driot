#pragma once
#include <gtest\gtest.h>
#include "../gyp_workspace2/FreeTypeImplementation.cpp"
FreeType_Implementation*ft;
TEST(FTCHECK, Init){
	
	EXPECT_NO_THROW(ft = new FreeType_Implementation());
}
FreeType_Face*fc;
TEST(FTCHECK, Face_init){
	EXPECT_NO_THROW(fc = new FreeType_Face(ft, "C:\\Windows\\Fonts\\arial.ttf"));


}
TEST(FTCHECK, Face_loadchar){
	EXPECT_NO_THROW(fc->set_font_size(33));
	EXPECT_NO_THROW(fc->load_char('X'));


}
