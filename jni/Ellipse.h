#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "CurveGraph.h"
#include <math.h>

/************************************************************************/
/* x^2/a^2 + y^2/b^2 = 1                                                */
/************************************************************************/
class Ellipse : public CurveGraph
{
private:
	float a;
	float b;
	double startAngle;
	double endAngle;
public:
	Ellipse(float a, float b, float centerX = 0, float centerY = 0, double start = 0, double end = 2*M_PI, bool empty = true);
	void draw(OpenglESProgram* openglESProgram, double sElapsed);
	bool isInObject(float x, float y);
};

#endif // !ELLIPSE_H
