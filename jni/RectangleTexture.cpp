#include "RectangleTexture.h"
#include "LogHelper.h"

const float RectangleTexture::BASE_L = 0.8f;

RectangleTexture::RectangleTexture(std::string picture, float startU, float startV,
								   float endU, float endV) {
	setWH(picture, startU, startV, endU, endV);
	init(0, 0, halfW, halfH, picture, startU, startV, endU, endV);
}

RectangleTexture::RectangleTexture(float centerX, float centerY, float w, float h,
								   std::string picture, float startU, float startV,
								   float endU, float endV) {
	init(centerX, centerY, w/2, h/2, picture, startU, startV, endU, endV);
}

void RectangleTexture::setWH(std::string picture, float startU, float startV,
							 float endU, float endV) {
	halfW = halfH = BASE_L;
	GraphicsTexture* graph = OpenglESHelper::getGraphicsTexture(picture.data());
	if (graph != NULL) {
		if(graph->loadWidthHeight()) {
			float scale = (graph->getWidth() * (endU - startU)) / (graph->getHeight() * (endV - startV));
			if (scale > 1) {
				halfH = halfW / scale;
			} else {
				halfW = halfH * scale;
			}
		}
		delete graph;
	}
}

void RectangleTexture::init(float centerX, float centerY, float halfw, float halfh,
							std::string picture, float startU, float startV, float endU, float endV) {
	this->startU = startU;
	this->startV = startV;
	this->endU = endU;
	this->endV = endV;
	this->picture = picture;
	this->halfW = halfw;
	this->halfH = halfh;
	moveTo(centerX, centerY);
	setInVec4(0, 0, halfW, halfH);

	pointNum = 4;
	float attrib[20] = {
		-halfW, halfH, 0.0f, startU, endV,
		-halfW, -halfH, 0.0f, startU, startV,
		halfW, halfH, 0.0f, endU, endV,
		halfW, -halfH, 0.0f, endU, startV
	};
	attribute = new float[20];
	memcpy(attribute, attrib, sizeof(attrib));
}

bool RectangleTexture::isInObject(float x, float y) {
	return x >= centerX-halfW && x <= centerX+halfW &&
		y >= centerY-halfH && y <= centerY+halfH;
}
