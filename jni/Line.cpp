#include "Line.h"

Line::Line(Point e) : start(), end() {
	float cx= (e.getX()) / 2;
	float cy = (e.getY()) / 2;
	start.set(-cx, -cy);
	end.set(cx, cy);
	moveTo(cx, cy);
	init();
}

Line::Line(Point s, Point e) : start(), end() {
	float cx= (s.getX() + e.getX()) / 2;
	float cy = (s.getY() + e.getY()) / 2;
	start.set(s.getX() - cx, s.getY() - cy);
	end.set(e.getX() - cx, e.getY() - cy);
	moveTo(cx, cy);
	init();
}

void Line::init() {
	pointNum = 2;
	attribute = new float[6];
	attribute[0] = start.getX();
	attribute[1] = start.getY();
	attribute[2] = 0;
	attribute[3] = end.getX();
	attribute[4] = end.getY();
	attribute[5] = 0;
}

Point Line::getStart() {
	return Point(start.getX() + centerX, start.getY() + centerY);
}

Point Line::getEnd() {
	return Point(end.getX() + centerX, end.getY() + centerY);
}

bool Line::isInObject(float x, float y) {
	return false;
}