#ifndef GRAPHOBJECT_H
#define GRAPHOBJECT_H

#include "BaseObject.h"

class GraphObject : public BaseObject
{
protected:
	float lineWidth;
	static const int STRIDE;

	GraphObject();

public:
	void setLineWidth(float width);
	void draw(OpenglESProgram* openglESProgram, double sElapsed);
};

#endif // !GRAPHOBJECT_H
