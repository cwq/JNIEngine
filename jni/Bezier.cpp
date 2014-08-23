#include "Bezier.h"
#include "Function.h"
#include "LogHelper.h"

Bezier::Bezier(Point s, Point c, Point e, bool empty /* = true */)
	: start(), control(), end() {
	
	this->empty = empty;

	centerX = (s.getX() + e.getX()) / 2;
	centerY = (s.getY() + e.getY()) / 2;
	start.set(s.getX() - centerX, s.getY() - centerY);
	control.set(c.getX() - centerX, c.getY() - centerY);
	end.set(e.getX() - centerX, e.getY() - centerY);
	moveTo(centerX, centerY);

	pointNum = CURVE_POINTS / 2;
	attribute = new float[pointNum * POINT_DIMENSION];

	//X(t)=(X0-2X1+X2)t^2+(-2X0+2X1)t+X0
	//Y(t)=(Y0-2Y1+Y2)t^2+(-2Y0+2Y1)t+Y0
	double dt = 1.0 / (pointNum - 1);
	double bx = 2.0 * (control.getX() - start.getX());
	double ax = start.getX() - 2 * control.getX() + end.getX();
	double by = 2.0 * (control.getY() - start.getY());
	double ay = start.getY() - 2 * control.getY() + end.getY();
	double tSquared;
	float tempX, tempY;
	int num = 0;
	for(double t = 0; t <= 1; t += dt) {
		tSquared = t * t;
		tempX = ax * tSquared + bx * t + start.getX();
		tempY = ay * tSquared + by * t + start.getY();

		if (tempX < minX) {
			minX = tempX;
		} else {
			if (tempX > maxX) {
				maxX = tempX;
			}
		}
		if (tempY < minY) {
			minY = tempY;
		} else {
			if (tempY > maxY) {
				maxY = tempY;
			}
		}
		attribute[num++] = tempX;
		attribute[num++] = tempY;
		attribute[num++] = 0;
	}
}

void Bezier::draw(OpenglESProgram* openglESProgram, double sElapsed) {
	if (empty) {
		GraphObject::draw(openglESProgram, sElapsed, GL_LINE_LOOP);
	} else {
		GraphObject::draw(openglESProgram, sElapsed, GL_TRIANGLE_FAN);
	}
}

bool Bezier::isInObject(float x, float y) {
	float finalX = x - centerX;
	float finalY = y - centerY;

	if (isOutBorder(finalX, finalY)) {
		return false;
	}

	if(!Function::sameDirection(Point(finalX, finalY), control, start, end)) {
		return false;
	}

	//过该点水平向左的射线与多边形交点数判断，奇数在内，偶数在外
	int i, j = pointNum - 1;
	bool isIn = false;
	int indexi, indexj;
	for (i = 0; i < pointNum; i++) {
		indexi = i * POINT_DIMENSION;
		indexj = j * POINT_DIMENSION;
		if (((attribute[indexi + 1] < finalY && attribute[indexj + 1] >= finalY)
			|| (attribute[indexj + 1] < finalY && attribute[indexi + 1] >= finalY))
			&& (attribute[indexi] <= finalX || attribute[indexj] <= finalX)) {
				//判断点在直线右边
				//xi + (y-yi) / (yj-yi) * (xj-xi) < x
				//xj=xi时：xi<x成立
				//yj=yi不可能进入
				if (attribute[indexi] + (finalY-attribute[indexi + 1]) /
					(attribute[indexj + 1] - attribute[indexi + 1]) *
					(attribute[indexj] - attribute[indexi]) < finalX) {
						isIn = !isIn;
				}
		}
		j = i;
	}
	return isIn;
}
