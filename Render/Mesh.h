
#include "Math.h"
#include "Vertex.h"
#include <string.h>

#ifndef _MESH_H
#define _MESH_H

class Mesh
{

public:

	_PSTR _name;

	_INT32 _verticesCount;

	Vertex* _vertices;

public:

	Mesh();
	
	Mesh(_PSTR name, _INT32 verticesCount);

	Mesh(const Mesh& other);

	~Mesh();

};

#endif