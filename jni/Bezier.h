#ifndef BEZIER_H
#define BEZIER_H

#include "CurveGraph.h"
#include "Point.h"

class Bezier : public CurveGraph
{
private:
	Point start;
	Point control;
	Point end;
public:
	Bezier(Point s, Point c, Point e, bool empty = true);
	void draw(OpenglESProgram* openglESProgram, double sElapsed);
	bool isInObject(float x, float y);
};

#endif // !BEZIER_H
