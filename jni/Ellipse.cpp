#include "Ellipse.h"
#include "Function.h"

Ellipse::Ellipse(float a, float b, float centerX /* = 0 */, float centerY /* = 0 */,
				 double start /* = 0 */, double end /* = 2*M_PI */, bool empty /* = true */) {
	this->a = a;
	this->b = b;
	this->centerX = centerX;
	this->centerY = centerY;
	this->empty = empty;
	startAngle = start;
	endAngle = end;
	if (endAngle < startAngle)
		endAngle += 2*M_PI;

	pointNum = (endAngle - startAngle) / (2*M_PI) * CURVE_POINTS + 2;

	bool isFull = ((endAngle - startAngle) == (2*M_PI));
	if (isFull)
		pointNum--;

	attribute = new float[pointNum * POINT_DIMENSION];
	int num = 0;

	if (!isFull) {
		attribute[num++] = 0;
		attribute[num++] = 0;
		attribute[num++] = 0;
	}

	double step = 2 * M_PI / CURVE_POINTS;
	float tempX, tempY;
	double p;
	for (double i = startAngle; i < endAngle + step; i += step) {
		p = a*b / sqrt(b*b*cos(i)*cos(i) + a*a*sin(i)*sin(i));
		tempX = p * cos(i);
		tempY = p * sin(i);

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

	moveTo(centerX, centerY);
}

void Ellipse::draw(OpenglESProgram* openglESProgram, double sElapsed) {
	if (empty) {
		GraphObject::draw(openglESProgram, sElapsed, GL_LINE_LOOP);
	} else {
		GraphObject::draw(openglESProgram, sElapsed, GL_TRIANGLE_FAN);
	}
}

bool Ellipse::isInObject(float x, float y) {
	float finalX = x - centerX;
	float finalY = y - centerY;

	if (isOutBorder(finalX, finalY)) {
		return false;
	}
	double angle = Function::angle(Point(finalX, finalY), Point(1, 0));
	if (finalY < 0)
		angle = M_PI * 2 - angle;
	if (angle < startAngle || angle > endAngle) {
		angle += M_PI * 2;
		if (angle < startAngle || angle > endAngle) {
			return false;
		}
	}
	if (b*b*finalX*finalX + a*a*finalY*finalY < a*a*b*b)
		return true;
	return false;
}
