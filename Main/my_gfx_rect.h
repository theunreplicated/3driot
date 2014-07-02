#ifndef INC_MY_GFX_RECT
#define INC_MY_GFX_RECT
#include <Windows.h>
class My_GFX_Rect{

public:
	My_GFX_Rect(const RECT& r);
	int width,height,x,y;
};
#endif