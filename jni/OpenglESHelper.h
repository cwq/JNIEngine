#ifndef OPENGLESHELPER_H
#define OPENGLESHELPER_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

class OpenglESHelper
{
public:
	static void readShaderString(char* &shaderString, const char* shaderName);
	static int loadShader(int type, const char* shaderSource);
	static int createProgram();
};

#endif // !OPENGLESHELPER_H
