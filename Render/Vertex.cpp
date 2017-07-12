#include "stdafx.h"
#include "Vertex.h"

Vertex::Vertex()
{
	_u = 1.0f;
	_v = 1.0f;
	_deepz = 0.0f;
}

Vertex::Vertex(Vector4f position, _FLOAT u, _FLOAT v, Color color)
{
	_position = position;
	_u = u;
	_v = v;
	_color = color;
	_deepz = 0.0f;
}

Vertex::Vertex(const Vertex& other)
{
	_position = other._position;
	_u = other._u;
	_v = other._v;
	_color = other._color;
	_deepz = other._deepz;
}

Vertex& Vertex::operator = (const Vertex& other)
{
	if (&other != this)
	{
		_position = other._position;
		_u = other._u;
		_v = other._v;
		_color = other._color;
		_deepz = other._deepz;
	}
	return *this;
}

Vertex Interpolate(Vertex& v1, Vertex& v2, _FLOAT t)
{
	Vertex ans = Vertex(
		Interpolate(v1._position, v2._position, t),
		Interpolate(v1._u, v2._u, t),
		Interpolate(v1._v, v2._v,t),
		Interpolate(v1._color, v2._color,t)
		);
	ans._deepz = Interpolate(v1._deepz, v2._deepz, t);
	return ans;
}

Vertex Vertex::operator - (const Vertex& other) const
{
	Vertex ans = Vertex(
		_position - other._position,
		_u - other._u,
		_v - other._v,
		_color - other._color
		);
	ans._position._w = _position._w - other._position._w;
	ans._deepz = _deepz - other._deepz;
	return ans;
}

Vertex Vertex::operator + (const Vertex& other) const
{
	Vertex ans = Vertex(
		_position + other._position,
		_u + other._u,
		_v + other._v,
		_color + other._color
		);
	ans._position._w = _position._w + other._position._w;
	ans._deepz = _deepz + other._deepz;
	return ans;
}

Vertex Vertex::operator * (_FLOAT scale) const
{
	Vertex ans = Vertex(
		_position * scale,
		_u * scale,
		_v * scale,
		_color * scale
		);
	ans._position._w = _position._w * scale;
	ans._deepz = _deepz * scale;
	return ans;
}

void Vertex::Init()
{
	_FLOAT inverse = 1.0f / _position._w;
	_deepz = inverse;
	_u *= inverse;
	_v *= inverse;
}