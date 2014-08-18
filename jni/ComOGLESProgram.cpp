#include "ComOGLESProgram.h"
#include "LogHelper.h"

//  /sdcard/JNIEngine/VertexShader.glsl
//  /sdcard/JNIEngine/FragmentShader.glsl

ComOGLESProgram::ComOGLESProgram()
	: vertexShaderName("VertexShader.glsl"),
	fragmentShaderName("FragmentShader.glsl") {
		OpenglESHelper::readShaderString(vertexShaderString, vertexShaderName);
		OpenglESHelper::readShaderString(fragmentShaderString, fragmentShaderName);
}

ComOGLESProgram::~ComOGLESProgram() {
	if (vertexShaderString != NULL) {
		free(vertexShaderString);
		vertexShaderString = NULL;
	}
	if (fragmentShaderString != NULL) {
		free(fragmentShaderString);
		fragmentShaderString = NULL;
	}
}

void ComOGLESProgram::onSurfaceCreated() {
	OpenglESProgram::onSurfaceCreated();
	int vertexShader = OpenglESHelper::loadShader(GL_VERTEX_SHADER, vertexShaderString);
	int fragmentShader = OpenglESHelper::loadShader(GL_FRAGMENT_SHADER, fragmentShaderString);
	program = OpenglESHelper::createProgram();
	LOGI(" %i program", program);
	if (program != 0) {
		//
		glAttachShader(program, vertexShader);
		glAttachShader(program,fragmentShader);
		glLinkProgram(program);
		GLint linkStatus = GL_FALSE;
		glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE) {
			GLint bufLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
			if (bufLength) {
				char* buf = (char*) malloc(bufLength);
				if (buf) {
					glGetProgramInfoLog(program, bufLength, NULL, buf);
					LOGE("Could not link program:\n%s\n", buf);
					free(buf);
				}
			}
			glDeleteProgram(program);
			program = 0;
		}
		//
		vertexLocation = glGetAttribLocation(program, vertexString);
		matrixLocation = glGetUniformLocation(program, matrixString);
		colorLocation = glGetUniformLocation(program, colorString);
		alphaLocation = glGetUniformLocation(program, alphaString);
		textureCoordinatesLocation = glGetAttribLocation(program, textureCoordinatesString);
		textureUnitLocation = glGetUniformLocation(program, textureUnitString);
		inVec4Location = glGetUniformLocation(program, inVec4String);
		showVec4Location = glGetUniformLocation(program, showVec4String);
		changeMatrixLocation = glGetUniformLocation(program, changeMatrixString);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	}
}
