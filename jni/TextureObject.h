#ifndef TEXTUREOBJECT_H
#define TEXTUREOBJECT_H

#include <string>
#include "BaseObject.h"

class TextureObject : public BaseObject
{
protected:
	TextureObject();

	static const int STRIDE;

	int textureID;
	std::string picture;

public:
	inline void setPicture(std::string p) {
		picture = p;
	}
	inline std::string getPicture() {
		return picture;
	}
	inline void setTextureID(int texture) {
		textureID = texture;
	}

	void addTextureToManager();
	void draw(OpenglESProgram* openglESProgram, double sElapsed);
};

#endif // !TEXTUREOBJECT_H
