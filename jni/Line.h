#ifndef LINE_H
#define LINE_H

#include "LinearGraph.h"
#include "Point.h"

class Line : public LinearGraph
{
private:
	Point start;
	Point end;
	void init();
public:
	Line(Point e);
	Line(Point s, Point e);
	Point getStart();
	Point getEnd();
	bool isInObject(float x, float y);
};

#endif // !LINE_H
