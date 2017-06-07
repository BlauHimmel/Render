#include "Math.h"

#ifndef _COLOR_H
#define _COLOR_H

class Color
{

public:

	_FLOAT _r, _g, _b;

public:

	Color();

	Color(_FLOAT r, _FLOAT g, _FLOAT b);

	Color(const Color& other);

	Color& operator = (const Color& other);

public:

	Color operator + (const Color& c) const;

	Color operator + (_FLOAT offset) const;

	Color operator - (const Color& c) const;

	Color operator - (_FLOAT offset) const;

	Color operator * (const Color& c) const;

	Color operator * (_FLOAT offset) const;

};

Color Interpolate(Color& c1, Color& c2, _FLOAT t);

#endif