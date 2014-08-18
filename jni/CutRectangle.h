#ifndef CUTRECTANGLE_H
#define CUTRECTANGLE_H

#include "MultiObject.h"
#include "RectangleTexture.h"

class CutRectangle : public MultiObject
{
private:
	RectangleTexture* topLeft;
	RectangleTexture* topRight;
	RectangleTexture* bottomLeft;
	RectangleTexture* bottomRight;
	RectangleTexture* upLayer;
	RectangleTexture* backRectTexture;

	BaseObject* select;

	float halfWCut;
	float halfHCut;
	float HALF_W_BACK;
	float HALF_H_BACK;

	BaseAnimation* downAnimation;
	BaseAnimation* upAnimation;

	float lastCenterX;
	float lastCenterY;

	static const float EDGE_L;
	static const float BIG_TO;
	static const float LEAST_HALFW;
	static const float LEAST_HALFH;
	static const float ANIMATION_TIME;
	static const std::string CUT_PICTURE;

	void updateUpLayer();
	float* getUV();
	bool isInCut(float x, float y);
	void moveVertex(float x, float y);

	float downX;
	float downY;

public:
	CutRectangle(RectangleTexture* backRectTexture, RectangleTexture* upLayer);
	~CutRectangle();

	void setBackRect(RectangleTexture* backRectTexture, RectangleTexture* upLayer, bool isFull = true);
	void doCutAnimation(RectangleTexture* tempTexture, RectangleTexture* finalTexture);
	RectangleTexture* getCutTempTexture();
	RectangleTexture* getCutFinalTexture();

	bool isInObject(float x, float y);
	void touchMove(float x, float y);
	void touchDown(float x, float y);
	void touchUp();

};

#endif // !CUTRECTANGLE_H
