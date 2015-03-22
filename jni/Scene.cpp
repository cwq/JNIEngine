#include "Scene.h"
#include "LogHelper.h"

static double now_ms() {
	struct timespec res;
	clock_gettime(CLOCK_REALTIME, &res);
	return 1000.0*res.tv_sec + (double)res.tv_nsec/1e6;
}

Scene::Scene() {
	openglESProgram = new ComOGLESProgram();
	objects = std::list<BaseObject*>();
	lastTime = 0;
	threadLock = new ThreadLock();
}

Scene::~Scene() {
	if (openglESProgram != NULL) {
		delete openglESProgram;
		openglESProgram = NULL;
	}
	if (threadLock != NULL) {
		delete threadLock;
		threadLock = NULL;
	}
	
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if ((*it) != NULL) {
			delete (*it);
			(*it) = NULL;
		}
	}
}

void Scene::onSurfaceCreated() {
	openglESProgram->onSurfaceCreated();
	TextureManager::reloadTextures();

	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->onSurfaceCreated();
	}

	lastTime = now_ms();
}

void Scene::onSurfaceChanged(int width, int height) {
	openglESProgram->onSurfaceChanged(width, height);
}

void Scene::onDrawFrame() {
	openglESProgram->onDrawFrame();
	TextureManager::loadTextures();

	double curTime = now_ms();
	//s
	double sElapsed = (curTime - lastTime) / 1000;
	lastTime = curTime;

	threadLock->lock();
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if ((*it) != NULL)
			(*it)->draw(openglESProgram, sElapsed);
	}
	threadLock->unlock();
}

void Scene::addObj(BaseObject* obj, int zOrder /* = 0 */) {
	obj->setzOrder(zOrder);
	std::list<BaseObject*>::iterator it;

	threadLock->lock();
	for (it = objects.begin(); it != objects.end(); ++it) {
		if ((*it) != NULL && zOrder < (*it)->getzOrder()) {
			break;
		}
	}
	objects.insert(it, obj);
	threadLock->unlock();

	obj->addTextureToManager();
}

void Scene::removeObj(BaseObject* obj) {
	threadLock->lock();
	objects.remove(obj);
	threadLock->unlock();
}

void Scene::clear() {
	threadLock->lock();
	objects.clear();
	threadLock->unlock();

	TextureManager::clearTextures();
}

void Scene::setBgColor(float r, float g, float b, float alpha) {
	openglESProgram->setBgColor(r, g, b, alpha);
}
