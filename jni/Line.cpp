#include "Line.h"

Line::Line(Point end) {
	init(Point(), end);
}

Line::Line(Point start, Point end) {
	init(start, end);
}

void Line::init(Point start, Point end) {
	float cx= (start.getX() + end.getX()) / 2;
	float cy = (start.getY() + end.getY()) / 2;
	moveTo(cx, cy);

	pointNum = 2;
	attribute = new float[6];
	attribute[0] = start.getX() - cx;
	attribute[1] = start.getY() - cy;
	attribute[2] = 0;
	attribute[3] = end.getX() - cx;
	attribute[4] = end.getY() - cy;
	attribute[5] = 0;
}

// Point Line::getStart() {
// 	return Point(start.getX() + centerX, start.getY() + centerY);
// }
// 
// Point Line::getEnd() {
// 	return Point(end.getX() + centerX, end.getY() + centerY);
// }

bool Line::isInObject(float x, float y) {
	return false;
}

void Line::draw(OpenglESProgram* openglESProgram, double sElapsed) {
	GraphObject::draw(openglESProgram, sElapsed, GL_LINES);
}
