#ifndef FUNCTION_H
#define FUNCTION_H

#include <math.h>

#include "Point.h"

class Function
{
public:
	static Point add(Point p1, Point p2);
	static Point subtract(Point p1, Point p2);
	static double dotProduct(Point p1, Point p2);
	static double crossProduct(Point p1, Point p2);

	static double distance(Point p1, Point p2);
	static double distance(Point p, Point l1, Point l2);

	static double angle(Point v1, Point v2);

	static bool sameDirection(Point p1, Point p2, Point l1, Point l2);
	static bool inTriangleUseDirection(Point p, Point end1, Point end2, Point end3);
	static bool inTriangleUseBarycenter(Point p, Point end1, Point end2, Point end3);
	static bool inTriangle(Point p, Point end1, Point end2, Point end3);
};

#endif // !FUNCTION_H
