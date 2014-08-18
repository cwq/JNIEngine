#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>
#include <map>

#include "OpenglESHelper.h"

class TextureManager
{
private:
	static std::map<std::string, int> textures;
	static bool isClear;
	static void clear();
public:
	static const int NO_TEXTURE;
	static void addTexture(std::string name);
	static int getTextureID(std::string name);
	static void loadTextures();
	static void reloadTextures();
	static void clearTextures();
};

#endif // !TEXTUREMANAGER_H
