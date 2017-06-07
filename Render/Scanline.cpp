#include "stdafx.h"
#include "Scanline.h"

Scanline::Scanline(Vertex start, Vertex step, _INT32 x, _INT32 y, _INT32 width)
{
	_start = start;
	_step = step;
	_x = x;
	_y = y;
	_width = width;
}