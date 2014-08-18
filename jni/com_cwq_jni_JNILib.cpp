#include <time.h>

#include "com_cwq_jni_JNILib.h"

#include "ComOGLESProgram.h"
#include "OpenglESHelper.h"
#include "LogHelper.h"
#include "RectangleTexture.h"
#include "MoveAnimation.h"
#include "MultiObject.h"
#include "FadeAnimation.h"
#include "ComplexAnimation.h"
#include "TintAnimation.h"
#include "RotateAnimation.h"
#include "ScaleAnimation.h"
#include "Scene.h"
#include "CutRectangle.h"

static const int TOUCH_DOWN = 0;
static const int TOUCH_UP = 1;
static const int TOUCH_MOVE = 2;

static Scene* scene = NULL;
static CutRectangle* cutRect = NULL;
static RectangleTexture* backRectTexture = NULL;
static RectangleTexture* upLayer = NULL;

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_initAssetManager(JNIEnv * env,
		jclass jthis, jobject assetManager) {
	AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
	OpenglESHelper::setAAssetManager(mgr);

	scene = new Scene();

	backRectTexture = new RectangleTexture("view1.png");
	upLayer = new RectangleTexture(0.0f, 0.0f,
			backRectTexture->getHalfW() * 2, backRectTexture->getHalfH() * 2,
			"");
	cutRect = new CutRectangle(backRectTexture, upLayer);

	scene->addObj(cutRect, 30);
	scene->addObj(upLayer, 20);
	scene->addObj(backRectTexture, 10);
	LOGI(" %s", "Java_com_cwq_jni_JNILib_initAssetManager");
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onSurfaceCreated(JNIEnv * env,
		jclass jthis) {
	LOGI(" %s", "Java_com_cwq_jni_JNILib_onSurfaceCreated 1");
	scene->onSurfaceCreated();

//	BaseAnimation* move = MoveAnimation::move(2, Point(0, 0), Point(1, 1));
//	move->setRevert(true);
//
//	BaseAnimation* fadeOut = FadeAnimation::fade(2.0f, 1, 0);
//	fadeOut->setRevert(true);
//
//	BaseAnimation* fadeIn = FadeAnimation::fade(2.0f, 0, 1);
//
//	BaseAnimation* rotateAnimation = RotateAnimation::rotate(2.0f,
//			mul->getRotateMatrix(), 360, 1, 1, 1);
//	rotateAnimation->setRevert(true);
//
//	BaseAnimation* tint = TintAnimation::tint(2.0f, mul->getColor(), 0, 1, 0, 1);
//	tint->setRevert(true);
//
//	BaseAnimation* scaleS = ScaleAnimation::scale(2.0f, 1, 0, 1, 0);
//	scaleS->setRevert(true);
//
//	BaseAnimation* scaleB = ScaleAnimation::scale(2.0f, 0, 1, 0, 1);
//
//	ComplexAnimation* c1 = new ComplexAnimation(2.0f);
//	c1->setRevert(true);
//	c1->addAnimation(scaleS);
//	c1->addAnimation(fadeOut);
//	c1->addAnimation(rotateAnimation);
//
//	ComplexAnimation* c2 = new ComplexAnimation(2.0f);
//	c2->setRevert(false);
//	c2->addAnimation(scaleB);
//	c2->addAnimation(fadeIn);
//	c2->addAnimation(rotateAnimation);
//
//	ComplexAnimation* c3 = new ComplexAnimation(2.0f);
//	c3->setRevert(true);
//	c3->addAnimation(move);
//	c3->addAnimation(tint);
//	c3->addAnimation(rotateAnimation);

	LOGI(" %s", "Java_com_cwq_jni_JNILib_onSurfaceCreated 2");
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onSurfaceChanged(JNIEnv * env,
		jclass jthis, jint width, jint height) {
	scene->onSurfaceChanged(width, height);
	LOGI(" %s", "Java_com_cwq_jni_JNILib_onSurfaceChanged");
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onDrawFrame(JNIEnv * env,
		jclass jthis) {
	scene->onDrawFrame();
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onTouch(JNIEnv * env,
		jclass jthis, jint type, jfloat x, jfloat y) {
	switch (type) {
		case TOUCH_DOWN:
			cutRect->touchDown(x, y);
			break;
		case TOUCH_MOVE:
			cutRect->touchMove(x, y);
			break;
		case TOUCH_UP:
			cutRect->touchUp();
			break;
		default:
			break;
	}
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_clickCut(JNIEnv * env,
		jclass jthis) {
	RectangleTexture* tempTexture = cutRect->getCutTempTexture();
	scene->addObj(tempTexture, 25);
	RectangleTexture* finalTexture = cutRect->getCutFinalTexture();
	cutRect->doCutAnimation(tempTexture, finalTexture);

	scene->removeObj(backRectTexture);
	scene->removeObj(upLayer);
	backRectTexture = finalTexture;
	upLayer = new RectangleTexture(0.0f, 0.0f, backRectTexture->getHalfW() * 2,
			backRectTexture->getHalfH() * 2, "");

	scene->addObj(upLayer, 20);
	scene->addObj(backRectTexture, 10);
	cutRect->setBackRect(backRectTexture, upLayer);

	scene->removeObj(tempTexture);
	delete tempTexture;
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_clickReset(JNIEnv * env,
		jclass jthis) {
	scene->removeObj(backRectTexture);
	scene->removeObj(upLayer);
	backRectTexture = new RectangleTexture("view1.png");
	upLayer = new RectangleTexture(0.0f, 0.0f, backRectTexture->getHalfW() * 2,
			backRectTexture->getHalfH() * 2, "");
	scene->addObj(upLayer, 20);
	scene->addObj(backRectTexture, 10);
	cutRect->setBackRect(backRectTexture, upLayer, false);
}
