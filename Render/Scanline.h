
#include "Math.h"
#include "Vertex.h"

#ifndef _SCANLINE_H
#define _SCANLINE_H

class Scanline
{

public:

	Vertex _start, _step;
	_INT32 _x, _y, _width;

public:

	Scanline(){}

	Scanline(Vertex start, Vertex step, _INT32 x, _INT32 y, _INT32 width);

};

#endif