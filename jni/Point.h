#ifndef POINT_H
#define POINT_H

class Point
{
private:
	float x;
	float y;

public:
	Point(float x = 0, float y = 0) {
		this->x = x;
		this->y = y;
	}

	inline float getX() {
		return x;
	}
	inline float getY() {
		return y;
	}
	inline void set(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

#endif // !POINT_H
