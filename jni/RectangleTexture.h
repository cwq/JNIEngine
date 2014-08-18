#ifndef RECTANGLETEXTURE_H
#define RECTANGLETEXTURE_H

#include "TextureObject.h"

class RectangleTexture : public TextureObject
{
private:
	float startU;
	float startV;
	float endU;
	float endV;
	static const float BASE_L;

	void setWH(std::string picture, float startU, float startV, float endU, float endV);
	void init(float centerX, float centerY, float halfw, float halfh, std::string picture,
		float startU, float startV, float endU, float endV);

protected:
	float halfW;
	float halfH;

public:
	RectangleTexture(std::string picture, float startU = 0, float startV = 0, float endU = 1, float endV = 1);
	RectangleTexture(float centerX, float centerY, float w, float h, std::string picture,
		float startU = 0, float startV = 0, float endU = 1, float endV = 1);

	inline float getHalfW() {
		return halfW;
	}
	inline float getHalfH() {
		return halfH;
	}
	inline float getStartU() {
		return startU;
	}
	inline float getStartV() {
		return startV;
	}
	inline float getEndU() {
		return endU;
	}
	inline float getEndV() {
		return endV;
	}

	bool isInObject(float x, float y);
};

#endif // !RECTANGLETEXTURE_H
