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

static OpenglESProgram* comProgram = NULL;
static MultiObject* mul = NULL;
static long lastTime = 0;

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_initAssetManager(JNIEnv * env,
		jclass jthis, jobject assetManager) {
	AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
	OpenglESHelper::setAAssetManager(mgr);
	comProgram = new ComOGLESProgram();
	BaseObject* rec = new RectangleTexture("view1.png");
	BaseObject* poin = new RectangleTexture(0, 0, 0.12f, 0.12f, "cut.png");
	mul = new MultiObject();
	mul->addObject(rec);
	mul->addObject(poin);
	mul->addTextureToManager();
	LOGI(" %s", "Java_com_cwq_jni_JNILib_initAssetManager");
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onSurfaceCreated(JNIEnv * env,
		jclass jthis) {
	LOGI(" %s", "Java_com_cwq_jni_JNILib_onSurfaceCreated 1");
	comProgram->onSurfaceCreated();
	TextureManager::reloadTextures();

	BaseAnimation* move = MoveAnimation::move(2, Point(0, 0), Point(1, 1));
	move->setRevert(true);

	BaseAnimation* fadeOut = FadeAnimation::fade(2.0f, 1, 0);
	fadeOut->setRevert(true);

	BaseAnimation* fadeIn = FadeAnimation::fade(2.0f, 0, 1);

	BaseAnimation* rotateAnimation = RotateAnimation::rotate(2.0f,
			mul->getRotateMatrix(), 360, 1, 1, 1);
	rotateAnimation->setRevert(true);

	BaseAnimation* tint = TintAnimation::tint(2.0f, mul->getColor(), 0, 1, 0, 1);
	tint->setRevert(true);

	BaseAnimation* scaleS = ScaleAnimation::scale(2.0f, 1, 0, 1, 0);
	scaleS->setRevert(true);

	BaseAnimation* scaleB = ScaleAnimation::scale(2.0f, 0, 1, 0, 1);

	ComplexAnimation* c1 = new ComplexAnimation(2.0f);
	c1->setRevert(true);
	c1->addAnimation(scaleS);
	c1->addAnimation(fadeOut);
	c1->addAnimation(rotateAnimation);

	ComplexAnimation* c2 = new ComplexAnimation(2.0f);
	c2->setRevert(false);
	c2->addAnimation(scaleB);
	c2->addAnimation(fadeIn);
	c2->addAnimation(rotateAnimation);

	ComplexAnimation* c3 = new ComplexAnimation(2.0f);
	c3->setRevert(true);
	c3->addAnimation(move);
	c3->addAnimation(tint);
	c3->addAnimation(rotateAnimation);

	mul->setAnimation(tint);
	lastTime = clock();
	LOGI(" %s", "Java_com_cwq_jni_JNILib_onSurfaceCreated 2");
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onSurfaceChanged(JNIEnv * env,
		jclass jthis, jint width, jint height) {
	comProgram->onSurfaceChanged(width, height);
	LOGI(" %s", "Java_com_cwq_jni_JNILib_onSurfaceChanged");
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onDrawFrame(JNIEnv * env,
		jclass jthis) {
	long curTime = clock();
	double sElapsed = ((double)curTime - lastTime) / CLOCKS_PER_SEC;
	lastTime = curTime;
	comProgram->onDrawFrame();
	TextureManager::loadTextures();
	mul->draw(comProgram, sElapsed);
}
