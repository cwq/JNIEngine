#include "BaseObject.h"

const int BaseObject::FLOAT_BYTE = 4;
const int BaseObject::POINT_DIMENSION = 3;
const int BaseObject::UV_DIMENSION = 2;

BaseObject::BaseObject() {
	centerX = 0;
	centerY = 0;
	alpha = 1;
	zOrder = 0;
	pointNum = 0;
	setColor(0, 0, 0, 0);
	setInVec4(0, 0, 10, 10);
	setShowVec4(0, 0, 10, 10);
	transMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	rotateMatrix = glm::mat4(1.0f);
	animationRunner = NULL;
	attribute = NULL;
}

BaseObject::~BaseObject() {
	if (attribute != NULL) {
		delete[] attribute;
		attribute = NULL;
	}
	if (animationRunner != NULL) {
		delete animationRunner;
		animationRunner = NULL;
	}
}

float BaseObject::getScaleX() {
	return scaleMatrix[0][0];
}

float BaseObject::getScaleY() {
	return scaleMatrix[1][1];
}

void BaseObject::setColor(float r, float g, float b, float a) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
}

void BaseObject::setInVec4(float centerX, float centerY, float halfW, float halfH) {
	inVec4[0] = centerX;
	inVec4[1] = centerY;
	inVec4[2] = halfW;
	inVec4[3] = halfH;
}

void BaseObject::setShowVec4(float centerX, float centerY, float halfW, float halfH) {
	showVec4[0] = centerX;
	showVec4[1] = centerY;
	showVec4[2] = halfW;
	showVec4[3] = halfH;
}

void BaseObject::moveTo(float x, float y) {
	centerX = x;
	centerY = y;
	transMatrix[3][0] = x;
	transMatrix[3][1] = y;
}

void BaseObject::moveBy(float dx, float dy) {
	centerX += dx;
	centerY += dy;
	transMatrix[3][0] += dx;
	transMatrix[3][1] += dy;
}

void BaseObject::rotateBy(float angle, float x, float y, float z) {
	rotateMatrix = glm::rotate(rotateMatrix, angle, glm::vec3(x, y, z));
}

void BaseObject::rotateTo(glm::mat4 rotate) {
	rotateMatrix = rotate;
}

void BaseObject::scaleBy(float scaleX, float scaleY) {
	scaleMatrix = glm::scale(scaleMatrix, glm::vec3(scaleX, scaleY, 1));
}

void BaseObject::scaleTo(float scaleX, float scaleY) {
	scaleMatrix[0][0] = scaleX;
	scaleMatrix[1][1] = scaleY;
}

void BaseObject::setAlphaBy(float deta) {
	this->alpha += deta;
}

void BaseObject::setAlphaTo(float alpha) {
	this->alpha = alpha;
}

bool BaseObject::isRunAnimation() {
	return animationRunner != NULL && animationRunner->isRun();
}

void BaseObject::setAnimation(BaseAnimation* animation) {
	if (animationRunner != NULL) {
		delete animationRunner;
		animationRunner = NULL;
	}
	animationRunner = new AnimationRunner(this, animation);
}

void BaseObject::doAnimation(double sElapsed) {
	if (animationRunner != NULL) {
		animationRunner->runAnimation(sElapsed);
	}
}

void BaseObject::addTextureToManager() {

}

void BaseObject::onSurfaceCreated() {

}
