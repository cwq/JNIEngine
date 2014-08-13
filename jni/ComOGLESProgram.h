#ifndef COMOGLESPROGRAM_H
#define COMOGLESPROGRAM_H

#include "openglesprogram.h"

class ComOGLESProgram :
	public OpenglESProgram
{
public:
	ComOGLESProgram();
	~ComOGLESProgram();
	void onSurfaceCreated();

private:
	char* vertexShaderString;
	char* fragmentShaderString;
	const char* vertexShaderName;
	const char* fragmentShaderName;
};

#endif // !COMOGLESPROGRAM_H