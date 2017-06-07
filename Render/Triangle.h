
#include "Vertex.h"

#ifndef _TRIANGLE_H
#define _TRIANGLE_H

class Triangle
{

public:

	Vertex _vertex1, _vertex2, _vertex3;

public:

	Triangle(){}

	Triangle(Vertex vertex1, Vertex vertex2, Vertex vertex3);

public:

	bool IsTriangle() const;

	void Sort();

};

#endif