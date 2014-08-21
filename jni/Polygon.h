#ifndef POLYGON_H
#define POLYGON_H

#include "list"

#include "LinearGraph.h"
#include "Point.h"

/************************************************************************/
/* 适用任何凸多边形，仅适用部分凹多边形且传入的点必须为某一凸点（凹点太深产生三角形在凹处显示）*/
/************************************************************************/
class Polygon : public LinearGraph
{
private:
	bool empty;
	float minX;
	float maxX;
	float minY;
	float maxY;
public:
	Polygon(std::list<Point> points, bool empty = true);
	void draw(OpenglESProgram* openglESProgram, double sElapsed);
	bool isInObject(float x, float y);
};

#endif // !POLYGON_H
