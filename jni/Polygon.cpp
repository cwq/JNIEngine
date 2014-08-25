#include "Polygon.h"
#include "Function.h"
#include "LogHelper.h"

Polygon::Polygon(std::list<Point> points, bool empty/* = true*/) {
	this->empty = empty;
	pointNum = points.size();
	attribute = new float[pointNum * POINT_DIMENSION];
	int num = 0;
	float cx = 0;
	float cy = 0;

	std::list<Point>::iterator it = points.begin();
 	float tempX, tempY;
// 	if (empty) {
		for (; it != points.end(); ++it) {
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
// 	} else {
// 		//0 2 4 6 5 3 1
// 		int index = 0;
// 		for (; it != points.end(); ++it, ++num) {
// 			tempX = (*it).getX();
// 			tempY = (*it).getY();
// 
// 			if (tempX < minX) {
// 				minX = tempX;
// 			} else {
// 				if (tempX > maxX) {
// 					maxX = tempX;
// 				}
// 			}
// 			if (tempY < minY) {
// 				minY = tempY;
// 			} else {
// 				if (tempY > maxY) {
// 					maxY = tempY;
// 				}
// 			}
// 
// 			cx += tempX;
// 			cy += tempY;
// 			
// 			if (num * 2 < pointNum) {
// 				index = num * 2;
// 			} else {
// 				index = (pointNum - num - 1) * 2 + 1;
// 			}
// 			index *= POINT_DIMENSION;
// 			attribute[index++] = tempX;
// 			attribute[index++] = tempY;
// 			attribute[index] = 0;
// 		}
// 	}
	
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

void Polygon::draw(OpenglESProgram* openglESProgram, double sElapsed) {
	if (empty) {
		GraphObject::draw(openglESProgram, sElapsed, GL_LINE_LOOP);
	} else {
		GraphObject::draw(openglESProgram, sElapsed, GL_TRIANGLE_FAN);
	}
}

bool Polygon::isInObject(float x, float y) {
	Point p(x - centerX, y - centerY);

	if (isOutBorder(p.getX(), p.getY())) {
		return false;
	}

	int index = 0;
	Point end1, end2, end3;
//	if (empty) {
		//过该点水平向左的射线与多边形交点数判断，奇数在内，偶数在外
		int i, j = pointNum - 1;
		bool isIn = false;
		int indexj;
		for (i = 0; i < pointNum; i++) {
			index = i * POINT_DIMENSION;
			indexj = j * POINT_DIMENSION;
			if (((attribute[index + 1] < p.getY() && attribute[indexj + 1] >= p.getY())
				|| (attribute[indexj + 1] < p.getY() && attribute[index + 1] >= p.getY()))
				&& (attribute[index] <= p.getX() || attribute[indexj] <= p.getX())) {
					//判断点在直线右边
					//xi + (y-yi) / (yj-yi) * (xj-xi) < x
					//xj=xi时：xi<x成立
					//yj=yi不可能进入
					if (attribute[index] + (p.getY()-attribute[index + 1]) /
						(attribute[indexj + 1] - attribute[index + 1]) *
						(attribute[indexj] - attribute[index]) < p.getX()) {
							isIn = !isIn;
					}
			}
			j = i;
		}
		return isIn;
// 		for (int num = 0; num < pointNum - 2; ++num) {
// 			//转为三角形
// 			if (num % 2 == 0) {
// 				//num/2  (pointNum - 1 - (num-1) / 2)
// 				//1
// 				index = (num / 2) * POINT_DIMENSION;
// 				end1.set(attribute[index], attribute[index + 1]);
// 				//2
// 				index = (pointNum - 1 - num / 2) * POINT_DIMENSION;
// 				end2.set(attribute[index], attribute[index + 1]);
// 				//3
// 				index = (num / 2 + 1) * POINT_DIMENSION;
// 				end3.set(attribute[index], attribute[index + 1]);
// 			} else {
// 				//1
// 				index = (pointNum - 1 - (num-1) / 2) * POINT_DIMENSION;
// 				end1.set(attribute[index], attribute[index + 1]);
// 				//2
// 				index = ((num + 1) / 2) * POINT_DIMENSION;
// 				end2.set(attribute[index], attribute[index + 1]);
// 				//3
// 				index = (pointNum - 1 - (num+1) / 2) * POINT_DIMENSION;
// 				end3.set(attribute[index], attribute[index + 1]);
// 			}
// 
// 			if (Function::inTriangle(p, end1, end2, end3))
// 				return true;
// 		}
// 	} else {
// 		for (int num = 0; num < pointNum - 2; ++num) {
// 			//1
// 			index = num * POINT_DIMENSION;
// 			end1.set(attribute[index], attribute[index + 1]);
// 			//2
// 			index += POINT_DIMENSION;
// 			end2.set(attribute[index], attribute[index + 1]);
// 			//3
// 			index += POINT_DIMENSION;
// 			end3.set(attribute[index], attribute[index + 1]);
// 
// 			if (Function::inTriangle(p, end1, end2, end3))
// 				return true;
// 		}
// 	}
// 	return false;
}
