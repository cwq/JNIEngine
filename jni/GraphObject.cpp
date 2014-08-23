#include "GraphObject.h"

const int GraphObject::STRIDE = (POINT_DIMENSION) * FLOAT_BYTE;

GraphObject::GraphObject() {
	lineWidth = 5;
	setColor(0, 0, 0, 1);

	empty = true;
	minX = 10;
	maxX = -10;
	minY = 10;
	maxY = -10;
/*	setInVec4(0, 0, 0, 0);*/
}

void GraphObject::setLineWidth(float width) {
	lineWidth = width;
}

bool GraphObject::isOutBorder(float x, float y) {
	if (x < minX || x > maxX || y < minY || y > maxY) {
		return true;
	}
	return false;
}

void GraphObject::draw(OpenglESProgram* openglESProgram, double sElapsed, GLenum mode) {
	doAnimation(sElapsed);

	glUseProgram(openglESProgram->getProgram());

	glLineWidth(lineWidth);

	glUniform4fv(openglESProgram->getColorLocation(), 1, color);
	glUniform1f(openglESProgram->getAlphaLocation(), alpha);

	glUniform4fv(openglESProgram->getInVec4Location(), 1, inVec4);
	glUniform4fv(openglESProgram->getShowVec4Location(), 1, showVec4);

	glm::mat4 complexMatrix = transMatrix * rotateMatrix * scaleMatrix;
	glUniformMatrix4fv(openglESProgram->getChangeMatrixLocation(), 1, GL_FALSE, &complexMatrix[0][0]);

	glm::mat4 finalMatrix = openglESProgram->getmMVPMatrix() * complexMatrix;
	glUniformMatrix4fv(openglESProgram->getMatrixLocation(), 1, GL_FALSE, &finalMatrix[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1f(openglESProgram->getTextureUnitLocation(), 0);

	glVertexAttribPointer(openglESProgram->getTextureCoordinatesLocation(), UV_DIMENSION, GL_FLOAT, GL_FALSE, STRIDE, attribute);
	glVertexAttribPointer(openglESProgram->getVertexLocation(), POINT_DIMENSION, GL_FLOAT, GL_FALSE, STRIDE, attribute);

	glEnableVertexAttribArray(openglESProgram->getVertexLocation());
	glEnableVertexAttribArray(openglESProgram->getTextureCoordinatesLocation());

	glDrawArrays(mode, 0, pointNum);

	glDisableVertexAttribArray(openglESProgram->getVertexLocation());
	glDisableVertexAttribArray(openglESProgram->getTextureCoordinatesLocation());
}
