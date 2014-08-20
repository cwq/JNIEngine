#ifndef LINE_H
#define LINE_H

#include "LinearGraph.h"
#include "Point.h"

class Line : public LinearGraph
{
private:
// 	Point start;
// 	Point end;
	void init(Point start, Point end);
public:
	Line(Point end);
	Line(Point start, Point end);
// 	Point getStart();
// 	Point getEnd();
	bool isInObject(float x, float y);
	void draw(OpenglESProgram* openglESProgram, double sElapsed);
};

#endif // !LINE_H
