#include "CutRectangle.h"
#include "ScaleAnimation.h"
#include "FadeAnimation.h"
#include "ComplexAnimation.h"
#include "TintAnimation.h"
#include "MoveAnimation.h"
#include "Point.h"

const float CutRectangle::EDGE_L = 0.12f;
const float CutRectangle::BIG_TO = 1.3f;
const float CutRectangle::LEAST_HALFH = 0.12f;
const float CutRectangle::LEAST_HALFW = 0.12f;
const float CutRectangle::ANIMATION_TIME = 0.3f;
const std::string CutRectangle::CUT_PICTURE = "cut.png";

CutRectangle::CutRectangle(RectangleTexture* backRectTexture, RectangleTexture* upLayer) {
	select = NULL;
	this->upLayer = NULL;
	this->backRectTexture = NULL;
	downX = downY = 0;
	topLeft = new RectangleTexture(0, 0, EDGE_L, EDGE_L, CUT_PICTURE);
	topRight = new RectangleTexture(0, 0, EDGE_L, EDGE_L, CUT_PICTURE);
	bottomLeft = new RectangleTexture(0, 0, EDGE_L, EDGE_L, CUT_PICTURE);
	bottomRight = new RectangleTexture(0, 0, EDGE_L, EDGE_L, CUT_PICTURE);
	addObject(topLeft);
	addObject(topRight);
	addObject(bottomLeft);
	addObject(bottomRight);

	downAnimation = ScaleAnimation::scale(ANIMATION_TIME, 1, BIG_TO, 1, BIG_TO);
	upAnimation = ScaleAnimation::scale(ANIMATION_TIME, BIG_TO, 1, BIG_TO, 1);

	setBackRect(backRectTexture, upLayer, false);
}

CutRectangle::~CutRectangle() {
	if (downAnimation != NULL) {
		delete downAnimation;
		downAnimation = NULL;
	}
	if (upAnimation != NULL) {
		delete upAnimation;
		upAnimation = NULL;
	}
}

void CutRectangle::setBackRect(RectangleTexture* backRectTexture,
							   RectangleTexture* upLayer, bool isFull /* = true */) {
	if (this->upLayer != NULL) {
		delete this->upLayer;
		this->upLayer = NULL;
	}
	if (this->backRectTexture != NULL) {
		delete this->backRectTexture;
		this->backRectTexture = NULL;
	}
	this->upLayer = upLayer;
	this->backRectTexture = backRectTexture;
	centerX = 0;
	centerY = 0;
	halfWCut = HALF_W_BACK = backRectTexture->getHalfW();
	halfHCut = HALF_H_BACK = backRectTexture->getHalfH();
	if (!isFull) {
		halfWCut *= 0.5;
		halfHCut *= 0.5;
	}

	topLeft->moveTo(centerX - halfWCut, centerY + halfHCut);
	topRight->moveTo(centerX + halfWCut, centerY + halfHCut);
	bottomLeft->moveTo(centerX -halfWCut, centerY - halfHCut);
	bottomRight->moveTo(centerX + halfWCut, centerY - halfHCut);

	upLayer->setAlphaTo(0);
	upLayer->setColor(0, 0, 0, 0.5f);
	updateUpLayer();

	if (!isFull) {
		upLayer->setColor(0, 0, 0, 0);
		upLayer->setAnimation(TintAnimation::tint(ANIMATION_TIME, upLayer->getColor(), 0, 0, 0, 0.5f));
		ComplexAnimation* inAnimation = new ComplexAnimation(ANIMATION_TIME);
		inAnimation->addAnimation(FadeAnimation::fade(ANIMATION_TIME, 0, 1));
		inAnimation->addAnimation(ScaleAnimation::scale(ANIMATION_TIME, 0.2f, 1, 0.2f, 1));
		this->setAnimation(inAnimation);
	}
}

void CutRectangle::updateUpLayer() {
	upLayer->setInVec4(centerX, centerY, halfWCut, halfHCut);
}

void CutRectangle::doCutAnimation(RectangleTexture* tempTexture, RectangleTexture* finalTexture) {
	//裁剪的小图拉伸动画
	ComplexAnimation* changeAnimation = new ComplexAnimation(ANIMATION_TIME);
	changeAnimation->addAnimation(MoveAnimation::move(ANIMATION_TIME, 
		Point(tempTexture->getCenterX(), tempTexture->getCenterY()), Point(0, 0)));
	float scaleX = finalTexture->getHalfW() / tempTexture->getHalfW();
	float scaleY = finalTexture->getHalfH() / tempTexture->getHalfH();
	BaseAnimation* scale = ScaleAnimation::scale(ANIMATION_TIME, 1, scaleX, 1, scaleY);
	changeAnimation->addAnimation(scale);
	tempTexture->setAnimation(changeAnimation);

	//    	//背景淡出
	//    	backRectTexture.setAnimation(FadeAnimation.fade(ANIMATION_TIME, 1, 0));
	//    	upLayer.setInVec4(0, 0, HALF_W_BACK, HALF_H_BACK);
	//    	upLayer.setAnimation(FadeAnimation.fade(ANIMATION_TIME, 0.5f, 0));

	//设置显示范围，使放大在一定范围内
	float halfW = backRectTexture->getHalfW() > finalTexture->getHalfW() ? backRectTexture->getHalfW() : finalTexture->getHalfW();
	float halfH = backRectTexture->getHalfH() > finalTexture->getHalfH() ? backRectTexture->getHalfH() : finalTexture->getHalfH();
	backRectTexture->setShowVec4(0, 0, halfW, halfH);
	upLayer->setShowVec4(0, 0, halfW, halfH);

	//背景图和蒙层拉伸动画
	ComplexAnimation* back = new ComplexAnimation(ANIMATION_TIME);
	back->addAnimation(MoveAnimation::move(ANIMATION_TIME, Point(0, 0),
		Point(-tempTexture->getCenterX() * scaleX, -tempTexture->getCenterY()*scaleY)));
	back->addAnimation(scale);
	backRectTexture->setAnimation(back);
	upLayer->setInVec4(0, 0, 0, 0);
	upLayer->setAnimation(back);

	//裁剪框顶点移动动画
	topLeft->setAnimation(MoveAnimation::move(ANIMATION_TIME, 
		Point(topLeft->getCenterX(), topLeft->getCenterY()),
		Point(-finalTexture->getHalfW(), finalTexture->getHalfH())));
	topRight->setAnimation(MoveAnimation::move(ANIMATION_TIME, 
		Point(topRight->getCenterX(), topRight->getCenterY()),
		Point(finalTexture->getHalfW(), finalTexture->getHalfH())));
	bottomLeft->setAnimation(MoveAnimation::move(ANIMATION_TIME, 
		Point(bottomLeft->getCenterX(), bottomLeft->getCenterY()),
		Point(-finalTexture->getHalfW(), -finalTexture->getHalfH())));
	bottomRight->setAnimation(MoveAnimation::move(ANIMATION_TIME, 
		Point(bottomRight->getCenterX(), bottomRight->getCenterY()),
		Point(finalTexture->getHalfW(), -finalTexture->getHalfH())));
	while(backRectTexture->isRunAnimation()) {

	}
}

float* CutRectangle::getUV() {
	float scaleU = (backRectTexture->getEndU() - backRectTexture->getStartU()) / HALF_W_BACK / 2;
	float scaleV = (backRectTexture->getEndV() - backRectTexture->getStartV()) / HALF_H_BACK / 2;
	float startU = backRectTexture->getStartU() + (centerX + HALF_W_BACK - halfWCut) * scaleU;
	float startV = backRectTexture->getStartV() + (HALF_H_BACK + centerY  - halfHCut) * scaleV;
	float endU = backRectTexture->getStartU() + (centerX + HALF_W_BACK + halfWCut) * scaleU;
	float endV = backRectTexture->getStartV() + (HALF_H_BACK + centerY  + halfHCut) * scaleV;
	float* uv = new float[4];
	uv[0] = startU;
	uv[1] = startV;
	uv[2] = endU;
	uv[3] = endV;
	return uv;
}

RectangleTexture* CutRectangle::getCutTempTexture() {
	float* uv = getUV();
	RectangleTexture* rec = new RectangleTexture(centerX, centerY, halfWCut * 2, halfHCut * 2, 
		backRectTexture->getPicture(), uv[0], uv[1], uv[2], uv[3]);
	delete uv;
	return rec;
}

RectangleTexture* CutRectangle::getCutFinalTexture() {
	float* uv = getUV();
	RectangleTexture* rec = new RectangleTexture(backRectTexture->getPicture(),
		uv[0], uv[1], uv[2], uv[3]);
	delete uv;
	return rec;
}

bool CutRectangle::isInCut(float x, float y) {
	return x >= centerX-halfWCut && x <= centerX+halfWCut && 
		y >= centerY-halfHCut && y <= centerY+halfHCut;
}

bool CutRectangle::isInObject(float x, float y) {
	if (topLeft->isInObject(x, y)) {
		select = topLeft;
		return true;
	}
	if (topRight->isInObject(x, y)) {
		select = topRight;
		return true;
	}
	if (bottomLeft->isInObject(x, y)) {
		select = bottomLeft;
		return true;
	}
	if (bottomRight->isInObject(x, y)) {
		select = bottomRight;
		return true;
	}
	if (isInCut(x, y)) {
		select = this;
		return true;
	}
	select = NULL;
	return false;
}

void CutRectangle::touchDown(float x, float y) {
	isInObject(x, y);
	downX = x;
	downY = y;
	if (select != NULL) {
		select->setAnimation(downAnimation);
		lastCenterX = select->getCenterX();
		lastCenterY = select->getCenterY();
	}
}

void CutRectangle::touchUp() {
	if (select != NULL) {
		select->setAnimation(upAnimation);
		select = NULL;
	}
}

void CutRectangle::touchMove(float x, float y) {
	if (select != NULL) {
		float dx = x - downX;
		float dy = y - downY;
		float cx = lastCenterX + dx;
		float cy = lastCenterY + dy;
		if (select == this) {
			//4个点都要在范围内  即  中心在 背景扣除裁剪框 的范围内
			if (cx < -HALF_W_BACK + halfWCut) {
				cx = -HALF_W_BACK + halfWCut;
			} else {
				if (cx > HALF_W_BACK - halfWCut) {
					cx = HALF_W_BACK - halfWCut;
				}
			}
			if (cy < -HALF_H_BACK + halfHCut) {
				cy = -HALF_H_BACK + halfHCut;
			} else {
				if (cy > HALF_H_BACK - halfHCut) {
					cy = HALF_H_BACK - halfHCut;
				}
			}
			select->moveTo(cx, cy);
		} else {
			if (cx < -HALF_W_BACK) {
				cx = -HALF_W_BACK;
			} else {
				if (cx > HALF_W_BACK) {
					cx = HALF_W_BACK;
				}
			}
			if (cy < -HALF_H_BACK) {
				cy = -HALF_H_BACK;
			} else {
				if (cy > HALF_H_BACK) {
					cy = HALF_H_BACK;
				}
			}
			moveVertex(cx, cy);
		}
		updateUpLayer();
	}
}

void CutRectangle::moveVertex(float x, float y) {
	if (select == topLeft) {
		if (x > centerX - LEAST_HALFW) {
			x = centerX - LEAST_HALFW;
		}
		if (y < centerY + LEAST_HALFH) {
			y = centerY + LEAST_HALFH;
		}
		topLeft->moveTo(x, y);
		topRight->moveTo(topRight->getCenterX(), y);
		bottomLeft->moveTo(x, bottomLeft->getCenterY());
	}
	else if (select == topRight) {
		if (x < centerX + LEAST_HALFW) {
			x = centerX + LEAST_HALFW;
		}
		if (y < centerY + LEAST_HALFH) {
			y = centerY + LEAST_HALFH;
		}
		topRight->moveTo(x, y);
		topLeft->moveTo(topLeft->getCenterX(), y);
		bottomRight->moveTo(x, bottomRight->getCenterY());
	}
	else if (select == bottomLeft) {
		if (x > centerX - LEAST_HALFW) {
			x = centerX - LEAST_HALFW;
		}
		if (y > centerY - LEAST_HALFH) {
			y = centerY - LEAST_HALFH;
		}
		bottomLeft->moveTo(x, y);
		topLeft->moveTo(x, topLeft->getCenterY());
		bottomRight->moveTo(bottomRight->getCenterX(), y);
	}
	else if (select == bottomRight) {
		if (x < centerX + LEAST_HALFW) {
			x = centerX + LEAST_HALFW;
		}
		if (y > centerY - LEAST_HALFH) {
			y = centerY - LEAST_HALFH;
		}
		bottomRight->moveTo(x, y);
		topRight->moveTo(x, topRight->getCenterY());
		bottomLeft->moveTo(bottomLeft->getCenterX(), y);
	}

	centerX = (topRight->getCenterX() + topLeft->getCenterX()) / 2;
	centerY = (topRight->getCenterY() + bottomRight->getCenterY()) / 2;
	halfWCut = (topRight->getCenterX() - topLeft->getCenterX()) / 2;
	halfHCut = (topRight->getCenterY() - bottomRight->getCenterY()) / 2;
}
