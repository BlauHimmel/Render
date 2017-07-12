#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle(Vertex vertex1, Vertex vertex2, Vertex vertex3)
{
	_vertex1 = vertex1;
	_vertex2 = vertex2;
	_vertex3 = vertex3;
}

bool Triangle::IsTriangle() const
{
	if (_vertex1._position._x == _vertex2._position._x &&
		_vertex1._position._x == _vertex3._position._x)
	{
		return false;
	}
	if (_vertex1._position._y == _vertex2._position._y &&
		_vertex1._position._y == _vertex3._position._y)
	{
		return false;
	}
	return true;
}
