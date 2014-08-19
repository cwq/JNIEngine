#include "Scene.h"
#include "LogHelper.h"

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

	lastTime = clock();
}

void Scene::onSurfaceChanged(int width, int height) {
	openglESProgram->onSurfaceChanged(width, height);
}

void Scene::onDrawFrame() {
	openglESProgram->onDrawFrame();
	TextureManager::loadTextures();

	long curTime = clock();
	double sElapsed = ((double)curTime - lastTime) / CLOCKS_PER_SEC;
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
