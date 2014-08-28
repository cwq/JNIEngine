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
	inline int getTextureID() {
		return textureID;
	}

	void addTextureToManager();
	void draw(OpenglESProgram* openglESProgram, double sElapsed);
	void onSurfaceCreated();
};

#endif // !TEXTUREOBJECT_H
