#ifndef POINT
#define POINT

#include "Vector.h"
class Point

{
public:
	float x, y, z;

	Point();
	Point(float a, float b, float c);

	Vector operator-(Point);
	Point operator+(Vector);
private:

};

inline Point::Point(){
	x = 0;
	y = 0;
	z = 0;
}

inline Point::Point(float a, float b, float c){
	x = a;
	y = b;
	z = c;
}

inline Vector Point::operator-(Point other){
	return Vector(x - other.x, y - other.y, z - other.z);
}


#endif