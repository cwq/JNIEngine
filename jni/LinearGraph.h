#ifndef LINEARGRAPH_H
#define LINEARGRAPH_H

#include "GraphObject.h"

class LinearGraph : public GraphObject
{
protected:
	LinearGraph();
	void draw(OpenglESProgram* openglESProgram, double sElapsed, GLenum mode);
};

#endif // !LINEARGRAPH_H
