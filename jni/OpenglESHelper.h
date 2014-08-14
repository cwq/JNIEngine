#ifndef OPENGLESHELPER_H
#define OPENGLESHELPER_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>

#include "GraphicsTexture.h"

class OpenglESHelper
{
public:
	static void readShaderString(char* &shaderString, const char* shaderName);
	static int loadShader(int type, const char* shaderSource);
	static int createProgram();
	static int createTexture(AAssetManager* assetManager, const char* pPath);
	static void deleteTexture(int n, const GLuint* texturs);
};

#endif // !OPENGLESHELPER_H
