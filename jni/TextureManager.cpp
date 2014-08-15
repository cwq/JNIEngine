#include "TextureManager.h"

#define NO_TEXTURE -1

std::map<std::string, int> TextureManager::textures = std::map<std::string, int>();

void TextureManager::addTexture(std::string name) {
	if (textures.find(name) != textures.end()) {
		textures[name] = NO_TEXTURE;
	}
}

int TextureManager::getTextureID(std::string name) {
	int texture = 0;
	std::map<std::string, int>::iterator temp = textures.find(name);
	if (temp != textures.end()) {
		texture = temp->second;
	}
	return texture;
}

void TextureManager::loadTextures() {
	std::map<std::string, int>::iterator it;
	for (it = textures.begin(); it != textures.end(); ++it) {
		if (it->second == NO_TEXTURE) {
			textures[it->first] = OpenglESHelper::createTexture(it->first.data());
		}
	}
}

void TextureManager::reloadTextures() {
	std::map<std::string, int>::iterator it;
	for (it = textures.begin(); it != textures.end(); ++it) {
		textures[it->first] = OpenglESHelper::createTexture(it->first.data());
	}
}

void TextureManager::clearTextures() {
	GLuint* texs = new GLuint[textures.size()];
	int num = 0;
	int texture = NO_TEXTURE;
	std::map<std::string, int>::iterator it;
	for (it = textures.begin(); it != textures.end(); ++it) {
		texture = it->second;
		if (texture != 0 && texture != NO_TEXTURE) {
			texs[num] = texture;
			num++;
		}
	}
	OpenglESHelper::deleteTexture(num, texs);
	textures.clear();
	delete[] texs;
}
