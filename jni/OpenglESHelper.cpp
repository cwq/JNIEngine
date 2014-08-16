#include "OpenglESHelper.h"
#include "LogHelper.h"

AAssetManager* OpenglESHelper::assetManager = NULL;

void OpenglESHelper::setAAssetManager(AAssetManager* asset) {
	assetManager = asset;
}

int OpenglESHelper::loadShader(int shaderType, const char* shaderSource) {
	if (shaderSource == NULL) {
		LOGE("%s", "shaderSource is null");
	}
	int shader = glCreateShader(shaderType);
	LOGI(" %i shader", shader);
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
 					LOGE("Could not compile shader %d:\n%s\n", shaderType, buf);
					free(buf);
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}
	} else {
		//error occurs creating the shader
		LOGE("%s", "error occurs creating the shader");
	}
	return shader;
}

int OpenglESHelper::createProgram() {
	int program = glCreateProgram();
	if (program == 0) {
		//error occurs creating the program
		LOGE("%s", "error occurs creating the program");
	}
	return program;
}

void OpenglESHelper::readShaderString(char* &shaderString, const char* shaderName) {
	AAsset* asset = AAssetManager_open(assetManager, shaderName, AASSET_MODE_UNKNOWN);
	if (asset == NULL) {
		LOGE(" %s", "asset==NULL");
		return;
	}
	off_t bufferSize = AAsset_getLength(asset);
	shaderString = (char *) malloc(bufferSize + 1);
	shaderString[bufferSize] = '\0';
	int numBytesRead = AAsset_read(asset, shaderString, bufferSize);
	AAsset_close(asset);

	//读取sdcard文件
//	FILE* file = fopen(shaderName, "r");
//	LOGI(" %i readShaderString", 0);
//	int count = 0;
//	if (file != NULL) {
//		fseek(file, 0, SEEK_END);
//		count = ftell(file);
//		rewind(file);
//		if (count > 0) {
//			LOGI(" %i readShaderString", 3);
//			shaderString = (char *)malloc(sizeof(char) * (count + 1));
//			count = fread(shaderString, sizeof(char), count, file);
//			shaderString[count] = '\0';
//		}
//		fclose(file);
//	} else {
//		LOGI("Can not open file: %s\n", shaderName);
//	}
}

GraphicsTexture* OpenglESHelper::getGraphicsTexture(const char* pPath) {
	if (pPath != NULL) {
		GraphicsTexture* graphicsTexture = new GraphicsTexture(assetManager, pPath);
		return graphicsTexture;
	}
	return NULL;
}

int OpenglESHelper::createTexture(const char* pPath) {
	int texture = 0;
	GraphicsTexture* graphicsTexture = getGraphicsTexture(pPath);
	if (graphicsTexture != NULL) {
		graphicsTexture->load();
		texture = graphicsTexture->getTextureId();
		delete graphicsTexture;
	}
	LOGI(" %i texture", texture);
	return texture;
}

void OpenglESHelper::deleteTexture(int n, const GLuint* texturs) {
	glDeleteTextures(n, texturs);
}
