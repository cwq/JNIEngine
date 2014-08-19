#include "CurveGraph.h"

CurveGraph::CurveGraph() {

}

void CurveGraph::draw(OpenglESProgram* openglESProgram, double sElapsed) {
	GraphObject::draw(openglESProgram, sElapsed);

	//draw bezier
// 	glVertexAttribPointer(openglESProgram->getVertexLocation(), POINT_DIMENSION, GL_FLOAT, GL_FALSE, STRIDE, attribute);
// 	glEnableVertexAttribArray(openglESProgram->getVertexLocation());
// 	glEnableVertexAttribArray(openglESProgram->getTextureCoordinatesLocation());
// 
// 	glDrawArrays(GL_LINE_LOOP, 0, pointNum);
// 
// 	glDisableVertexAttribArray(openglESProgram->getVertexLocation());
// 	glDisableVertexAttribArray(openglESProgram->getTextureCoordinatesLocation());
}