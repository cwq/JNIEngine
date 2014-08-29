#include <time.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <ui/GraphicBuffer.h>
#include <ui/PixelFormat.h>

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
static GLuint textureID = 0;
static GLuint mTextureId = 0;

static PFNEGLCREATEIMAGEKHRPROC _eglCreateImageKHR = NULL;
static PFNEGLDESTROYIMAGEKHRPROC _eglDestroyImageKHR = NULL;
static PFNGLEGLIMAGETARGETTEXTURE2DOESPROC _glEGLImageTargetTexture2DOES = NULL;

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
	_eglCreateImageKHR = (PFNEGLCREATEIMAGEKHRPROC) eglGetProcAddress("eglCreateImageKHR");
	_eglDestroyImageKHR = (PFNEGLDESTROYIMAGEKHRPROC) eglGetProcAddress("eglDestroyImageKHR");
	_glEGLImageTargetTexture2DOES = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");	if(_eglCreateImageKHR == NULL ||
		_eglDestroyImageKHR == NULL ||
		_glEGLImageTargetTexture2DOES == NULL)
	{
		LOGE("EGLImage is not supported!\n");
		exit(1);
	}
/*	textureID = OpenglESHelper::createTexture("view1.png");*/

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
	if (isSave) {
		//EGLImageKHR
		android::GraphicBuffer* buffer = new android::GraphicBuffer(200, 150, android::PIXEL_FORMAT_RGBA_8888,
			android::GraphicBuffer::USAGE_HW_TEXTURE |
			android::GraphicBuffer::USAGE_HW_2D |
			android::GraphicBuffer::USAGE_SW_READ_OFTEN |
			android::GraphicBuffer::USAGE_SW_WRITE_OFTEN);

		android::status_t err = buffer->initCheck();
		if (err != android::NO_ERROR)
		{
			LOGE("GraphicBuffer creation failed! Err:%s\n", strerror(-err));
		}

		android_native_buffer_t* anb = buffer->getNativeBuffer();
		// Convert the native buffer handle onto the commonly used EGL handle.
		EGLClientBuffer nativeBufferHandle = (EGLClientBuffer)anb;

		EGLint eglImgAttrs[] = { EGL_IMAGE_PRESERVED_KHR, EGL_TRUE, EGL_NONE, EGL_NONE };
		EGLImageKHR image = _eglCreateImageKHR(eglGetCurrentDisplay(), EGL_NO_CONTEXT, EGL_NATIVE_BUFFER_ANDROID, nativeBufferHandle, eglImgAttrs);
		/* Check EGL errors */
		EGLint egl_error = eglGetError();
		if(egl_error != EGL_SUCCESS)
		{
			LOGE("eglCreateImageKHR failed! Error: %X\n", egl_error);
			exit(1);
		}

		if (textureID != 0)
			glDeleteTextures(1, &textureID);
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		_glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		LOGI("textureID: %i ", textureID);

		//glReadPixels
		long s = clock();
		//use created framebuffer
		glGenFramebuffers(1, &frameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		LOGI("FBO: %i , glCheckFramebufferStatus: %i", frameBuffer, status);

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
		if (mTextureId != 0)
			glDeleteTextures(1, &mTextureId);
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

/*		glDeleteTextures(1, &mTextureId);*/
		glDeleteFramebuffers(1, &frameBuffer);
		LOGI("mTextureId: %i", mTextureId);
	} else {
		scene->onDrawFrame();
	}
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_onTouch(JNIEnv * env,
		jclass jthis, jint type, jfloat x, jfloat y) {

}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_clickCut(JNIEnv * env,
		jclass jthis) {
	frame->setTextureID(0);
}

JNIEXPORT void JNICALL Java_com_cwq_jni_JNILib_clickReset(JNIEnv * env,
		jclass jthis) {
	isSave = true;

}
