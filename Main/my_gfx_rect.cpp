#include "my_gfx_rect.h"
#include <complex>
My_GFX_Rect::My_GFX_Rect(const RECT& r){
	//http://src.chromium.org/viewvc/chrome/trunk/src/ui/gfx/geometry/rect.cc?revision=263101
	//=Betrag
	width = std::abs(r.right - r.left);
	height=std::abs(r.bottom - r.top);
	x = r.left;
	y = r.top;//ich glaub ,dass ich es so wie in der Chrome impl gemacht habe,bin jedoch nicht ganz sicher,vllt. habe ich auch die left und top vertauscht
}