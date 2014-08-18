#include "TextureObject.h"
#include "LogHelper.h"

const int TextureObject::STRIDE = (POINT_DIMENSION + UV_DIMENSION) * FLOAT_BYTE;

TextureObject::TextureObject() {
	textureID = TextureManager::NO_TEXTURE;
	picture = "";
}

void TextureObject::addTextureToManager() {
	if (!picture.empty()) {
		TextureManager::addTexture(picture);
	}
}

void TextureObject::onSurfaceCreated() {
	setTextureID(TextureManager::NO_TEXTURE);
}

void TextureObject::draw(OpenglESProgram* openglESProgram, double sElapsed) {
	if (textureID == TextureManager::NO_TEXTURE) {
		setTextureID(TextureManager::getTextureID(picture));
	}

	doAnimation(sElapsed);

	glUseProgram(openglESProgram->getProgram());

	glVertexAttribPointer(openglESProgram->getVertexLocation(), POINT_DIMENSION, GL_FLOAT, GL_FALSE, STRIDE, attribute);
	glVertexAttribPointer(openglESProgram->getTextureCoordinatesLocation(), UV_DIMENSION, GL_FLOAT, GL_FALSE, STRIDE, attribute + POINT_DIMENSION);

	glEnableVertexAttribArray(openglESProgram->getVertexLocation());
	glEnableVertexAttribArray(openglESProgram->getTextureCoordinatesLocation());

	glUniform4fv(openglESProgram->getColorLocation(), 1, color);
	glUniform1f(openglESProgram->getAlphaLocation(), alpha);

	glUniform4fv(openglESProgram->getInVec4Location(), 1, inVec4);
	glUniform4fv(openglESProgram->getShowVec4Location(), 1, showVec4);

	glm::mat4 complexMatrix = transMatrix * rotateMatrix * scaleMatrix;
	glUniformMatrix4fv(openglESProgram->getChangeMatrixLocation(), 1, GL_FALSE, &complexMatrix[0][0]);

	glm::mat4 finalMatrix = openglESProgram->getmMVPMatrix() * complexMatrix;
	glUniformMatrix4fv(openglESProgram->getMatrixLocation(), 1, GL_FALSE, &finalMatrix[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1f(openglESProgram->getTextureUnitLocation(), 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, pointNum);

	glDisableVertexAttribArray(openglESProgram->getVertexLocation());
	glDisableVertexAttribArray(openglESProgram->getTextureCoordinatesLocation());
}
