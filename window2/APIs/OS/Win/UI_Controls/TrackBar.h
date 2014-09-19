#pragma once
#include "../../../../Window.h"
struct TrackBar_Value_Pairs{
	UINT min, max;

};
class TrackBar{
	Windows::Window * window_handle;
public:
	TrackBar(LPCSTR name, Windows::WindowRect rect, Windows::Window*mw, TrackBar_Value_Pairs range_values, TrackBar_Value_Pairs selction_values);

};