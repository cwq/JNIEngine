#ifndef LINEARGRAPH_H
#define LINEARGRAPH_H

#include "GraphObject.h"

class LinearGraph : public GraphObject
{
protected:
	LinearGraph();
public:
	void draw(OpenglESProgram* openglESProgram, double sElapsed);
};

#endif // !LINEARGRAPH_H
