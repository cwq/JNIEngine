#include "MultiObject.h"

MultiObject::MultiObject() {
	centerX = 0;
	centerY = 0;
	objects = std::list<BaseObject*>();
}

MultiObject::~MultiObject() {
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if ((*it) != NULL) {
			delete (*it);
			(*it) = NULL;
		}
	}
}

void MultiObject::addObject(BaseObject* object) {
	objects.push_back(object);
}

void MultiObject::setAlphaBy(float deta) {
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->setAlphaBy(deta);
	}
}

void MultiObject::setAlphaTo(float alpha) {
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->setAlphaTo(alpha);
	}
}

void MultiObject::setColor(float r, float g, float b, float a) {
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->setColor(r, g, b, a);
	}
}

void MultiObject::moveBy(float dx, float dy) {
	centerX += dx;
	centerY += dy;
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->moveBy(dx, dy);
	}
}

void MultiObject::moveTo(float x, float y) {
	moveBy(x - centerX, y - centerY);
}

void MultiObject::rotateBy(float angle, float x, float y, float z) {
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->rotateBy(angle, x, y, z);
	}
}

void MultiObject::rotateTo(glm::mat4 rotate) {
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->rotateTo(rotate);
	}
}

void MultiObject::scaleBy(float scaleX, float scaleY) {
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->scaleBy(scaleX, scaleY);
	}
}

void MultiObject::scaleTo(float scaleX, float scaleY) {
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->scaleTo(scaleX, scaleY);
	}
}

void MultiObject::draw(OpenglESProgram* openglESProgram, double sElapsed) {
	doAnimation(sElapsed);
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->draw(openglESProgram, sElapsed);
	}
}

bool MultiObject::isInObject(float x, float y) {
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if ((*it)->isInObject(x, y)) {
			return true;
		}
	}
	return false;
}

void MultiObject::addTextureToManager() {
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->addTextureToManager();
	}
}

void MultiObject::onSurfaceCreated() {
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->onSurfaceCreated();
	}
}
