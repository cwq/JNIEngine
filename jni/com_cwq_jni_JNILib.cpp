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
#include "Line.h"
#include "Polygon.h"
#include "Ellipse.h"
#include "Bezier.h"
#include "TriangulatePolygon.h"

static Scene* scene = NULL;
static BaseObject* temp = NULL;

static int w;
static int h;
static RectangleTexture* frame = NULL;
static bool isSave = false;
static GLubyte* pixelBuffer = NULL;
static GLuint frameBuffer;
static GLuint textureID;

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_initAssetManager(JNIEnv * env,
		jclass jthis, jobject assetManager) {
	AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
	OpenglESHelper::setAAssetManager(mgr);

	scene = new Scene();

	std::vector<Point> points;
	points.push_back(Point(-0.9f, 0.9f));
	points.push_back(Point(-0.9f, 0.0f));
	points.push_back(Point(-0.5, 0.0f));
	points.push_back(Point(-0.4f, 0.2f));
	points.push_back(Point(-0.1f, 0.2f));
	points.push_back(Point(0.3, 0.0f));
	points.push_back(Point(0.6f, 0.0f));
	points.push_back(Point(0.8f, 0.4f));
	points.push_back(Point(0.3f, 0.4f));
	points.push_back(Point(0.3f, 0.6f));
	points.push_back(Point(0.5f, 0.6f));
	points.push_back(Point(0.5f, 0.9f));
	points.push_back(Point(-0.1f, 0.9f));
	points.push_back(Point(-0.4f, 0.5f));
	points.push_back(Point(-0.7f, 0.9f));

	temp = new TriangulatePolygon(points);
	temp->setAlphaTo(0.5);
	temp->setColor(1, 0, 0, 0.5);

	frame = new RectangleTexture(0.0f, 0.0f,
		0.8 * 2, 0.6 * 2,
		"");
	scene->addObj(frame);
	LOGI(" %s", "Java_com_cwq_jni_JNILib_initAssetManager");
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onSurfaceCreated(JNIEnv * env,
		jclass jthis) {
	LOGI(" %s", "Java_com_cwq_jni_JNILib_onSurfaceCreated 1");
	scene->onSurfaceCreated();

	glGenFramebuffers(1, &frameBuffer);
	textureID = OpenglESHelper::createTexture("view1.png");

	LOGI(" %s", "Java_com_cwq_jni_JNILib_onSurfaceCreated 2");
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onSurfaceChanged(JNIEnv * env,
		jclass jthis, jint width, jint height) {
	w = width;
	h = height;
	scene->onSurfaceChanged(width, height);
	LOGI(" %s", "Java_com_cwq_jni_JNILib_onSurfaceChanged");
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onDrawFrame(JNIEnv * env,
		jclass jthis) {
/*	scene->onDrawFrame();*/
	if (isSave) {
		//
		long s = clock();
		//use created framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		LOGI("glCheckFramebufferStatus: %i", status);

// 		GLuint rboid;
// 		glGenRenderbuffers(1, &rboid);
// 		glBindRenderbuffer(GL_RENDERBUFFER, rboid);
// 		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, 200, 150);
// 
// 		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboid);
// 		status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
// 		LOGI("glCheckFramebufferStatus: %i", status);

		//draw
		glViewport(0,0,200,150);
		temp->draw(scene->getOpenglESProgram(), 0);

		//read pixels
		long e = clock();
		LOGI("%f s used Framebuffer", ((double)e - s) / CLOCKS_PER_SEC);
		pixelBuffer = (GLubyte*)malloc(200*150*4);
		s = clock();
		glReadPixels(0, 0, 200, 150, GL_RGBA, GL_UNSIGNED_BYTE, pixelBuffer);
		e = clock();
		LOGI("%f s used glReadPixels", ((double)e - s) / CLOCKS_PER_SEC);
		
		// Creates a new OpenGL texture.
		GLuint mTextureId;
		glGenTextures(1, &mTextureId);
		glBindTexture(GL_TEXTURE_2D, mTextureId);
		// Set-up texture properties.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Loads image data into OpenGL.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 200, 150, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, pixelBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		isSave = false;
		free(pixelBuffer);
		//use system default framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, w, h);

		frame->setTextureID(mTextureId);
		scene->onDrawFrame();

		glDeleteTextures(1, &mTextureId);
/*		glDeleteRenderbuffers(1, &rboid);*/
		glDeleteFramebuffers(1, &frameBuffer);
	}
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onTouch(JNIEnv * env,
		jclass jthis, jint type, jfloat x, jfloat y) {

}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_clickCut(JNIEnv * env,
		jclass jthis) {

}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_clickReset(JNIEnv * env,
		jclass jthis) {
	isSave = true;

}
