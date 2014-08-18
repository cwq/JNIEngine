#ifndef GRAPHICSTEXTURE_H
#define GRAPHICSTEXTURE_H

#include "Resource.h"

#include <GLES2/gl2.h>
#include <png.h>

class GraphicsTexture
{
public:
	GraphicsTexture(AAssetManager* assetManager, const char* pPath);
	~GraphicsTexture();

	int32_t getHeight();
	int32_t getWidth();

	int load();
	void unload();
	GLuint getTextureId();
	bool loadWidthHeight();

protected:
	uint8_t* loadImage();

private:
	static void callback_read(png_structp pStruct, png_bytep pData, png_size_t pSize);
	Resource mResource;
	GLuint mTextureId;
	int32_t mWidth, mHeight;
	GLint mFormat;

};

#endif // !GRAPHICSTEXTURE_H
