#include "OpenglESHelper.h"

int OpenglESHelper::loadShader(int shaderType, const char* shaderSource) {
	int shader = glCreateShader(shaderType);
	if (shader) {
		glShaderSource(shader, 1, &shaderSource, NULL);
		glCompileShader(shader);
		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen) {
				char* buf = (char*) malloc(infoLen);
				if (buf) {
					glGetShaderInfoLog(shader, infoLen, NULL, buf);
// 					LOGE("Could not compile shader %d:\n%s\n", shaderType, buf);
					free(buf);
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}
	} else {
		//error occurs creating the shader
	}
	return shader;
}

int OpenglESHelper::createProgram() {
	int program = glCreateProgram();
	if (program == 0) {
		//error occurs creating the program
	}
	return program;
}

void OpenglESHelper::readShaderString(char* &shaderString, const char* shaderName) {
	FILE* file = fopen(shaderName, "r");
	int count = 0;
	if (file != NULL) {
		fseek(file, 0, SEEK_END);
		count = ftell(file);
		rewind(file);
		if (count > 0) {
			shaderString = (char *)malloc(sizeof(char) * (count + 1));
			count = fread(shaderString, sizeof(char), count, file);
			shaderString[count] = '\0';
		}
		fclose(file);
	} else {
		printf("Can not open file: %s\n", shaderName);
	}
}

int OpenglESHelper::createTexture(AAssetManager* assetManager, const char* pPath) {
	int texture = 0;
	GraphicsTexture graphicsTexture(assetManager, pPath);
	graphicsTexture.load();
	texture = graphicsTexture.getTextureId();
	return texture;
}

void OpenglESHelper::deleteTexture(int n, const GLuint* texturs) {
	glDeleteTextures(n, texturs);
}
