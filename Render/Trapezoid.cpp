#include "stdafx.h"
#include "Trapezoid.h"

Trapezoid::Trapezoid(_FLOAT top, _FLOAT bottom, Line left, Line right)
{
	_top = top;
	_bottom = bottom;
	_left = left;
	_right = right;
}

_INT32 Trapezoid::GetTrapezoids(const Triangle& triangle, Trapezoid* trapezoids)
{
	if (trapezoids == NULL)
	{
		return 0;
	}

	Vertex v1 = triangle._vertex1;
	Vertex v2 = triangle._vertex2;
	Vertex v3 = triangle._vertex3;

	if (v1._position._y > v2._position._y)
	{
		Swap(v1, v2);
	}

	if (v1._position._y > v3._position._y)
	{
		Swap(v1, v3);
	}

	if (v2._position._y > v3._position._y)
	{
		Swap(v2, v3);
	}

	if (triangle.IsTriangle() == false)
	{
		return 0;
	}

	if (v1._position._y == v2._position._y)
	{
		if (v1._position._x > v2._position._x)
		{
			Swap(v1, v2);
		}
		if (v1._position._y >= v3._position._y)
		{
			return 0;
		}
		trapezoids[0]._top = v1._position._y;
		trapezoids[0]._bottom = v3._position._y;
		trapezoids[0]._left._vertex1 = v1;
		trapezoids[0]._left._vertex2 = v3;
		trapezoids[0]._right._vertex1 = v2;
		trapezoids[0]._right._vertex2 = v3;
		return 1;
	}

	if (v2._position._y == v3._position._y)
	{
		if (v2._position._x > v3._position._x)
		{
			Swap(v2, v3);
		}
		if (v1._position._y >= v3._position._y)
		{
			return 0;
		}
		trapezoids[0]._top = v1._position._y;
		trapezoids[0]._bottom = v3._position._y;
		trapezoids[0]._left._vertex1 = v1;
		trapezoids[0]._left._vertex2 = v2;
		trapezoids[0]._right._vertex1 = v1;
		trapezoids[0]._right._vertex2 = v3;
		return 1;
	}

	trapezoids[0]._top = v1._position._y;
	trapezoids[0]._bottom = v2._position._y;
	trapezoids[1]._top = v2._position._y;
	trapezoids[1]._bottom = v3._position._y;


	_FLOAT x, k;
	k = (v3._position._y - v1._position._y) / (v2._position._y - v1._position._y);
	x = (v2._position._x - v1._position._x) * k + v1._position._x;

	if (x < v3._position._x)
	{
		trapezoids[0]._left._vertex1 = v1;
		trapezoids[0]._left._vertex2 = v2;
		trapezoids[0]._right._vertex1 = v1;
		trapezoids[0]._right._vertex2 = v3;
		trapezoids[1]._left._vertex1 = v2;
		trapezoids[1]._left._vertex2 = v3;
		trapezoids[1]._right._vertex1 = v1;
		trapezoids[1]._right._vertex2 = v3;
	}
	else
	{
		trapezoids[0]._left._vertex1 = v1;
		trapezoids[0]._left._vertex2 = v3;
		trapezoids[0]._right._vertex1 = v1;
		trapezoids[0]._right._vertex2 = v2;
		trapezoids[1]._left._vertex1 = v1;
		trapezoids[1]._left._vertex2 = v3;
		trapezoids[1]._right._vertex1 = v2;
		trapezoids[1]._right._vertex2 = v3;
	}
	return 2;
}

void Trapezoid::GetEndPoint(_FLOAT y)
{
	_FLOAT tLeft = (y - _left._vertex1._position._y) / 
		(_left._vertex2._position._y - _left._vertex1._position._y) ;
	_FLOAT tRight = (y - _right._vertex1._position._y) /
		(_right._vertex2._position._y - _right._vertex1._position._y);
	_left._v = Interpolate(_left._vertex1, _left._vertex2, tLeft);
	_right._v = Interpolate(_right._vertex1, _right._vertex2, tRight);
}

Scanline Trapezoid::InitScanline(_INT32 y)
{
	_FLOAT width = _right._v._position._x - _left._v._position._x;
	Scanline scanline;
	scanline._x = (_INT32)(_left._v._position._x + 0.5f);
	scanline._y = y;
	scanline._start = _left._v;
	scanline._width = (_INT32)(_right._v._position._x + 0.5f) - (_INT32)(_left._v._position._x + 0.5f);
	if (_left._v._position._x >= _right._v._position._x)
	{
		scanline._width = 0;
	}
	scanline._step = (_right._v - _left._v) * (1.0f / width);
	return scanline;
}