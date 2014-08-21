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
	Point v0 = subtract(end3, end1);
	Point v1 = subtract(end2, end1);
	Point v2 = subtract(p, end1);

	double dot00 = dotProduct(v0, v0);
	double dot01 = dotProduct(v0, v1);
	double dot02 = dotProduct(v0, v2);
	double dot11 = dotProduct(v1, v1);
	double dot12 = dotProduct(v1, v2);

	double inverDeno = 1 / (dot00 * dot11 - dot01 * dot01);
	double u = (dot11 * dot02 - dot01 * dot12) * inverDeno;
	if (u < 0 || u > 1)
		return false;
	double v = (dot00 * dot12 - dot01 * dot02) * inverDeno;
	if (v < 0 || v > 1)
		return false;

	return (u + v) <= 1;
}

bool Function::inTriangle(Point p, Point end1, Point end2, Point end3) {
	return inTriangleUseDirection(p, end1, end2, end3);
}