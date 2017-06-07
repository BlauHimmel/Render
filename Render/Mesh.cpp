#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh()
{
	_name = new _CHAR[128];
	_vertices = NULL;
	_verticesCount = 0;
}

Mesh::Mesh(_PSTR name, _INT32 verticesCount)
{
	_name = new _CHAR[128];
	strcpy_s(_name, 128, name);
	_verticesCount = verticesCount;
	_vertices = new Vertex[verticesCount];
}


Mesh::Mesh(const Mesh& other)
{
	strcpy_s(_name, 128, other._name);
	_verticesCount = other._verticesCount;
	if (_verticesCount > 0)
	{
		if (_vertices != NULL)
		{
			delete[] _vertices;
			_vertices = NULL;
		}
		_vertices = new Vertex[_verticesCount];
		for (auto i = 0; i < _verticesCount; i++)
		{
			_vertices[i] = other._vertices[i];
		}
	}
	else
	{
		if (_vertices != NULL)
		{
			delete[] _vertices;
			_vertices = NULL;
		}
	}
}

Mesh::~Mesh()
{
	if (_vertices != NULL)
	{
		delete[] _vertices;
		_vertices = NULL;
	}
	delete[] _name;
}