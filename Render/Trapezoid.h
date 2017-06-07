
#include "Math.h"
#include "Line.h"
#include "Triangle.h"
#include "Scanline.h"

#ifndef _TRAPEZOID_H
#define _TRAPEZOID_H

class Trapezoid
{

public:

	_FLOAT _top, _bottom;
	Line _left, _right;

public:

	Trapezoid(){}

	Trapezoid(_FLOAT top, _FLOAT bottom, Line left, Line right);

	static _INT32 GetTrapezoids(const Triangle& triangle, Trapezoid* trapezoids);

	void GetEndPoint(_FLOAT y);

	Scanline InitScanline(_INT32 y);

};

#endif