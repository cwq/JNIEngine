#ifndef GRAPHOBJECT_H
#define GRAPHOBJECT_H

#include "BaseObject.h"

class GraphObject : public BaseObject
{
protected:
	float lineWidth;
	static const int STRIDE;

	GraphObject();
	void draw(OpenglESProgram* openglESProgram, double sElapsed, GLenum mode);

public:
	void setLineWidth(float width);
};

#endif // !GRAPHOBJECT_H
