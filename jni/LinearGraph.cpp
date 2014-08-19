#include "LinearGraph.h"

LinearGraph::LinearGraph() {

}

void LinearGraph::draw(OpenglESProgram* openglESProgram, double sElapsed) {
	GraphObject::draw(openglESProgram, sElapsed);

	glVertexAttribPointer(openglESProgram->getVertexLocation(), POINT_DIMENSION, GL_FLOAT, GL_FALSE, STRIDE, attribute);
	glEnableVertexAttribArray(openglESProgram->getVertexLocation());
	glEnableVertexAttribArray(openglESProgram->getTextureCoordinatesLocation());

	glDrawArrays(GL_LINE_LOOP, 0, pointNum);

	glDisableVertexAttribArray(openglESProgram->getVertexLocation());
	glDisableVertexAttribArray(openglESProgram->getTextureCoordinatesLocation());
}