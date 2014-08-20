#include "Polygon.h"
#include "Function.h"

Polygon::Polygon(std::list<Point> points, bool empty/* = true*/) {
	this->empty = empty;
	pointNum = points.size();
	attribute = new float[pointNum * POINT_DIMENSION];
	int num = 0;
	float cx = 0;
	float cy = 0;

	if (empty) {
		for (std::list<Point>::iterator it = points.begin(); it != points.end(); ++it) {
			cx += (*it).getX();
			cy += (*it).getY();
			attribute[num++] = (*it).getX();
			attribute[num++] = (*it).getY();
			attribute[num++] = 0;
		}
	} else {
		//0 2 4 6 5 3 1
		int index = 0;
		for (std::list<Point>::iterator it = points.begin(); it != points.end(); ++it, ++num) {
			cx += (*it).getX();
			cy += (*it).getY();
			
			if (num * 2 < pointNum) {
				index = num * 2;
			} else {
				index = (pointNum - num - 1) * 2 + 1;
			}
			index *= POINT_DIMENSION;
			attribute[index++] = (*it).getX();
			attribute[index++] = (*it).getY();
			attribute[index] = 0;
		}
	}
	
	cx /= pointNum;
	cy /= pointNum;
	for (num = 0; num < pointNum; ++num) {
		attribute[num * POINT_DIMENSION] -= cx;
		attribute[num * POINT_DIMENSION + 1] -= cy;
	}
	moveTo(cx, cy);
}

void Polygon::draw(OpenglESProgram* openglESProgram, double sElapsed) {
	if (empty) {
		LinearGraph::draw(openglESProgram, sElapsed, GL_LINE_LOOP);
	} else {
		LinearGraph::draw(openglESProgram, sElapsed, GL_TRIANGLE_STRIP);
	}
}

bool Polygon::isInObject(float x, float y) {
	Point p(x - centerX, y - centerY);
	int index = 0;
	if (empty) {

	} else {
		Point end1, end2, end3;
		for (int num = 0; num < pointNum - 2; ++num) {
			//1
			index = num * POINT_DIMENSION;
			end1.set(attribute[index], attribute[index + 1]);
			//2
			index += POINT_DIMENSION;
			end2.set(attribute[index], attribute[index + 1]);
			//3
			index += POINT_DIMENSION;
			end3.set(attribute[index], attribute[index + 1]);

			if (Function::inTriangle(p, end1, end2, end3))
				return true;
		}
	}
	return false;
}