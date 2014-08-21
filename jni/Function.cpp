#include "Function.h"

Point Function::add(Point p1, Point p2) {
	return Point(p1.getX() + p2.getX(), p1.getY() + p2.getY());
}

Point Function::subtract(Point p1, Point p2) {
	return Point(p1.getX() - p2.getX(), p1.getY() - p2.getY());
}

double Function::dotProduct(Point p1, Point p2) {
	return p1.getX() * p2.getX() + p1.getY() * p2.getY();
}

double Function::crossProduct(Point p1, Point p2) {
	return p1.getX() * p2.getY() - p2.getX() * p1.getY();
}

double Function::distance(Point p1, Point p2) {
	return sqrt((p1.getX() - p2.getX()) * (p1.getX() - p2.getX()) +
		(p1.getY() - p2.getY()) * (p1.getY() - p2.getY()));
}

double Function::distance(Point p, Point l1, Point l2) {
	double dis = 0;
	if (l1.getX() == l2.getX()) {
		dis = p.getX() - l1.getX();
	} else if (l1.getY() == l2.getY()) {
		dis = p.getY() - l1.getY();
	} else {
		double A = l1.getY() - l2.getY();
		double B = l1.getX() - l2.getX();
		dis = fabs(A * p.getX() - B * p.getY()) / sqrt(A * A + B * B);
	}
	return dis;
}

bool Function::sameDirection(Point p1, Point p2, Point l1, Point l2) {
	Point v1 = subtract(l1, l2);
	Point v2 = subtract(p2, l2);
	Point v3 = subtract(p1, l2);

	bool cross1 = crossProduct(v1, v2) >= 0;
	bool cross2 = crossProduct(v1, v3) >= 0;

	return (cross1 == cross2);
}

bool Function::inTriangleUseDirection(Point p, Point end1, Point end2, Point end3) {
	return sameDirection(p, end1, end2, end3) &&
		sameDirection(p, end2, end3, end1) &&
		sameDirection(p, end3, end1, end2);
}

bool Function::inTriangleUseBarycenter(Point p, Point end1, Point end2, Point end3) {
	return false;
}