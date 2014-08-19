#ifndef CURVEGRAPH_H
#define CURVEGRAPH_H

#include "GraphObject.h"

class CurveGraph : public GraphObject
{
protected:
	CurveGraph();
public:
	void draw(OpenglESProgram* openglESProgram, double sElapsed);
};

#endif // !CURVEGRAPH_H
