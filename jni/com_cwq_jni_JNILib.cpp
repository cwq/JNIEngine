
#include "com_cwq_jni_JNILib.h"

#include "ComOGLESProgram.h"
#include "OpenglESHelper.h"
#include "LogHelper.h"
#include "RectangleTexture.h"

static OpenglESProgram* comProgram = NULL;
static BaseObject* rec = NULL;
static BaseObject* poin = NULL;

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_initAssetManager(JNIEnv * env,
		jclass jthis, jobject assetManager) {
	AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
	OpenglESHelper::setAAssetManager(mgr);
	comProgram = new ComOGLESProgram();
	rec = new RectangleTexture("view1.png");
	rec->addTextureToManager();
	poin = new RectangleTexture(0, 0, 0.12f, 0.12f, "cut.png");
//	poin->setColor(0.8f, 0.8f, 0.8f, 0);
	poin->addTextureToManager();
	LOGI(" %s", "Java_com_cwq_jni_JNILib_initAssetManager");
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onSurfaceCreated(JNIEnv * env,
		jclass jthis) {
	LOGI(" %s", "Java_com_cwq_jni_JNILib_onSurfaceCreated 1");
	comProgram->onSurfaceCreated();
	TextureManager::reloadTextures();
	LOGI(" %s", "Java_com_cwq_jni_JNILib_onSurfaceCreated 2");
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onSurfaceChanged(JNIEnv * env,
		jclass jthis, jint width, jint height) {
	comProgram->onSurfaceChanged(width, height);
	LOGI(" %s", "Java_com_cwq_jni_JNILib_onSurfaceChanged");
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onDrawFrame(JNIEnv * env,
		jclass jthis) {
	comProgram->onDrawFrame();
	TextureManager::loadTextures();
	rec->draw(comProgram, 0);
	poin->draw(comProgram, 0);
}
