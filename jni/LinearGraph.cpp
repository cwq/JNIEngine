#include "LinearGraph.h"

LinearGraph::LinearGraph() {
	
}

void LinearGraph::draw(OpenglESProgram* openglESProgram, double sElapsed, GLenum mode) {
	GraphObject::draw(openglESProgram, sElapsed);

	glVertexAttribPointer(openglESProgram->getVertexLocation(), POINT_DIMENSION, GL_FLOAT, GL_FALSE, STRIDE, attribute);
	glEnableVertexAttribArray(openglESProgram->getVertexLocation());
	glEnableVertexAttribArray(openglESProgram->getTextureCoordinatesLocation());

	glDrawArrays(mode, 0, pointNum);

	glDisableVertexAttribArray(openglESProgram->getVertexLocation());
	glDisableVertexAttribArray(openglESProgram->getTextureCoordinatesLocation());
}