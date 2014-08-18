#ifndef MULTIOBJECT_H
#define MULTIOBJECT_H

#include <list>

#include "BaseObject.h"

class MultiObject : public BaseObject
{
private:
	std::list<BaseObject*> objects;

public:
	MultiObject();
	~MultiObject();

	void addObject(BaseObject* object);

	void setAlphaBy(float deta);
	void setAlphaTo(float alpha);
	void setColor(float r, float g, float b, float a);
	void moveTo(float x, float y);
	void moveBy(float dx, float dy);
	void rotateBy(float angle, float x, float y, float z);
	void rotateTo(glm::mat4 rotate);
	void scaleBy(float scaleX, float scaleY);
	void scaleTo(float scaleX, float scaleY);
	void draw(OpenglESProgram* openglESProgram, double sElapsed);
	bool isInObject(float x, float y);
	void addTextureToManager();
	void onSurfaceCreated();
};

#endif // !MULTIOBJECT_H
