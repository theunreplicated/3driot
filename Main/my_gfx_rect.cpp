#include "my_gfx_rect.h"
#include <complex>
My_GFX_Rect::My_GFX_Rect(const RECT& r){
	//http://src.chromium.org/viewvc/chrome/trunk/src/ui/gfx/geometry/rect.cc?revision=263101
	//=Betrag
	width = std::abs(r.right - r.left);
	height=std::abs(r.bottom - r.top);
	x = 0;
	y = 0;//@TODO:so machen wie in IMpl
}