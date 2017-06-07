
#include "Math.h"
#include "Vertex.h"

#ifndef _LINE_H
#define _LINE_H

class Line
{

public:

	Vertex _v, _vertex1, _vertex2;

public:

	Line(){}

	Line(Vertex v, Vertex vertex1, Vertex vertex2);

};

#endif