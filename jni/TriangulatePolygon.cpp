#include "TriangulatePolygon.h"
#include "Function.h"

static const float EPSILON=0.0000000001f;

TriangulatePolygon::TriangulatePolygon(std::vector<Point> points) {
	this->empty = false;

	std::list<Point> result;
	triangulate(points, result);

	pointNum = result.size();
	attribute = new float[pointNum * POINT_DIMENSION];
	int num = 0;
	float cx = 0;
	float cy = 0;
	std::list<Point>::iterator it = result.begin();
	float tempX, tempY;
	for (; it != result.end(); ++it) {
		tempX = (*it).getX();
		tempY = (*it).getY();

		if (tempX < minX) {
			minX = tempX;
		} else {
			if (tempX > maxX) {
				maxX = tempX;
			}
		}
		if (tempY < minY) {
			minY = tempY;
		} else {
			if (tempY > maxY) {
				maxY = tempY;
			}
		}

		cx += tempX;
		cy += tempY;

		attribute[num++] = tempX;
		attribute[num++] = tempY;
		attribute[num++] = 0;
	}
	cx /= pointNum;
	cy /= pointNum;
	minX -= cx;
	maxX -= cx;
	minY -= cy;
	maxY -= cy;
	for (num = 0; num < pointNum; ++num) {
		attribute[num * POINT_DIMENSION] -= cx;
		attribute[num * POINT_DIMENSION + 1] -= cy;
	}
	moveTo(cx, cy);
}

float TriangulatePolygon::Area(std::vector<Point> contour) {
	int n = contour.size();

	float A=0.0f;

	for(int p=n-1,q=0; q<n; p=q++)
	{
		A+= contour[p].getX()*contour[q].getY() - contour[q].getX()*contour[p].getY();
	}
	return A*0.5f;
}

bool TriangulatePolygon::Snip(std::vector<Point> contour, int u, int v, int w, int n, int *V) {
	int p;
	float Ax, Ay, Bx, By, Cx, Cy, Px, Py;

	Ax = contour[V[u]].getX();
	Ay = contour[V[u]].getY();

	Bx = contour[V[v]].getX();
	By = contour[V[v]].getY();

	Cx = contour[V[w]].getX();
	Cy = contour[V[w]].getY();

	if ( EPSILON > (((Bx-Ax)*(Cy-Ay)) - ((By-Ay)*(Cx-Ax))) ) return false;

	for (p=0;p<n;p++)
	{
		if( (p == u) || (p == v) || (p == w) ) continue;
// 		Px = contour[V[p]].getX();
// 		Py = contour[V[p]].getY();
// 		if (InsideTriangle(Ax,Ay,Bx,By,Cx,Cy,Px,Py)) return false;
		if (Function::inTriangle(contour[V[p]], contour[V[u]], contour[V[v]], contour[V[w]]))
			return false;
	}

	return true;
}

void TriangulatePolygon::triangulate(std::vector<Point> contour, std::list<Point> &result) {
	/* allocate and initialize list of Vertices in polygon */

	int n = contour.size();
	/*  if ( n < 3 ) return false;*/

	int *V = new int[n];

	/* we want a counter-clockwise polygon in V */

	if (0.0f < Area(contour))
		for (int v = 0; v < n; v++)
			V[v] = v;
	else
		for (int v = 0; v < n; v++)
			V[v] = (n - 1) - v;

	int nv = n;

	/*  remove nv-2 Vertices, creating 1 triangle every time */
	int count = 2 * nv; /* error detection */

	for (int m = 0, v = nv - 1; nv > 2;) {
		/* if we loop, it is probably a non-simple polygon */
		if (0 >= (count--)) {
			//** Triangulate: ERROR - probable bad polygon!
			/*      return false;*/
		}

		/* three consecutive vertices in current polygon, <u,v,w> */
		int u = v;
		if (nv <= u)
			u = 0; /* previous */
		v = u + 1;
		if (nv <= v)
			v = 0; /* new v    */
		int w = v + 1;
		if (nv <= w)
			w = 0; /* next     */

		if (Snip(contour, u, v, w, nv, V)) {
			int a, b, c, s, t;

			/* true names of the vertices */
			a = V[u];
			b = V[v];
			c = V[w];

			/* output Triangle */
			result.push_back(contour[a]);
			result.push_back(contour[b]);
			result.push_back(contour[c]);

			m++;

			/* remove v from remaining polygon */
			for (s = v, t = v + 1; t < nv; s++, t++)
				V[s] = V[t];
			nv--;

			/* resest error detection counter */
			count = 2 * nv;
		}
	}
	delete V;
}

void TriangulatePolygon::draw(OpenglESProgram* openglESProgram, double sElapsed) {
	GraphObject::draw(openglESProgram, sElapsed, GL_TRIANGLES);
}

bool TriangulatePolygon::isInObject(float x, float y) {
	Point p(x - centerX, y - centerY);

	if (isOutBorder(p.getX(), p.getY())) {
		return false;
	}

	int index = 0;
	Point end1, end2, end3;
	for (int num = 0; num < pointNum - 2; num += 3) {
		//1
		index = num * POINT_DIMENSION;
		end1.set(attribute[index], attribute[index + 1]);
		//2
		index += POINT_DIMENSION;
		end2.set(attribute[index], attribute[index + 1]);
		//3
		index += POINT_DIMENSION;
		end3.set(attribute[index], attribute[index + 1]);

		if (Function::inTriangle(p, end1, end2, end3))
			return true;
	}
	return false;
}
