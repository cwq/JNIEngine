#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <stlport/hash_map>

class TextureManager
{
private:
	static hash_map<char*, int> textures;
};

#endif // !TEXTUREMANAGER_H
