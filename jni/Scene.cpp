#include "Scene.h"

Scene::Scene() {
	openglESProgram = new ComOGLESProgram();
	objects = std::list<BaseObject*>();
	lastTime = 0;
}

Scene::~Scene() {
	if (openglESProgram != NULL) {
		delete openglESProgram;
		openglESProgram = NULL;
	}
	
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		if ((*it) != NULL)
			delete (*it);
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
	for (std::list<BaseObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
		(*it)->draw(openglESProgram, sElapsed);
	}
}

void Scene::addObj(BaseObject* obj, int zOrder /* = 0 */) {
	obj->setzOrder(zOrder);
	std::list<BaseObject*>::iterator it;
	for (it = objects.begin(); it != objects.end(); ++it) {
		if (zOrder < (*it)->getzOrder()) {
			break;
		}
	}
	objects.insert(it, obj);
	obj->addTextureToManager();
}

void Scene::removeObj(BaseObject* obj) {
	objects.remove(obj);
}

void Scene::clear() {
	objects.clear();
	TextureManager::clearTextures();
}

void Scene::setBgColor(float r, float g, float b, float alpha) {
	openglESProgram->setBgColor(r, g, b, alpha);
}