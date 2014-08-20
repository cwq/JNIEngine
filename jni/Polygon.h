#ifndef POLYGON_H
#define POLYGON_H

#include "list"

#include "LinearGraph.h"
#include "Point.h"

class Polygon : public LinearGraph
{
private:
	bool empty;
public:
	Polygon(std::list<Point> points, bool empty = true);
	void draw(OpenglESProgram* openglESProgram, double sElapsed);
	bool isInObject(float x, float y);
};

#endif // !POLYGON_H
