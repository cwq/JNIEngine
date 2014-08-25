#ifndef POLYGON_H
#define POLYGON_H

#include "list"

#include "LinearGraph.h"
#include "Point.h"

/************************************************************************/
/* 适用任何凸多边形   !!改为只适用凸多边形 和 空心凹多边形。        */
/* 实心凹多边形使用TriangulatePolygon     */
/************************************************************************/
class Polygon : public LinearGraph
{
public:
	Polygon(std::list<Point> points, bool empty = true);
	void draw(OpenglESProgram* openglESProgram, double sElapsed);
	bool isInObject(float x, float y);
};

#endif // !POLYGON_H
