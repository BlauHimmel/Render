#include "Math.h"
#include "Color.h"

#ifndef _VERTEX_H
#define _VERTEX_H

class Vertex
{
	
public:

	Vector4f _position;
	_FLOAT _u, _v;
	Color _color;
	_FLOAT _deepz;

public:

	Vertex();

	Vertex(Vector4f position, _FLOAT u, _FLOAT v, Color color);

	Vertex(const Vertex& other);

	Vertex& operator = (const Vertex& other);

public:

	Vertex operator - (const Vertex& other) const;

	Vertex operator + (const Vertex& other) const;

	Vertex operator * (_FLOAT scale) const;

public:

	void Init();

};

Vertex Interpolate(Vertex& v1, Vertex& v2, _FLOAT t);


#endif