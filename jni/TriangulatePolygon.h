#ifndef TRIANGLULATEPOLYGON_H
#define TRIANGLULATEPOLYGON_H

#include "list"
#include "vector"

#include "LinearGraph.h"
#include "Point.h"

/************************************************************************/
/* 适用实心凹多边形（划分为多个三角形）     */
/************************************************************************/
class TriangulatePolygon : public LinearGraph
{
private:
	// compute area of a contour/polygon
	float Area(std::vector<Point> contour);
	// triangulate a contour/polygon, places results in STL vector
	// as series of triangles.
	void triangulate(std::vector<Point> contour, std::list<Point> &result);

	bool Snip(std::vector<Point> contour, int u, int v, int w, int n, int *V);
public:
	TriangulatePolygon(std::vector<Point> points);
	void draw(OpenglESProgram* openglESProgram, double sElapsed);
	bool isInObject(float x, float y);
};

#endif // !TRIANGLULATEPOLYGON_H
