#ifndef GRAPHOBJECT_H
#define GRAPHOBJECT_H

#include "BaseObject.h"

class GraphObject : public BaseObject
{
protected:
	float lineWidth;
	static const int STRIDE;

	bool empty;
	float minX;
	float maxX;
	float minY;
	float maxY;

	GraphObject();
	void draw(OpenglESProgram* openglESProgram, double sElapsed, GLenum mode);

	bool isOutBorder(float x, float y);

public:
	void setLineWidth(float width);
};

#endif // !GRAPHOBJECT_H
