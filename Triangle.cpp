#include "Triangle.h"


Triangle::Triangle(void)
{
	v1 = Point(-1,0,-2);
	v2 = Point(1,0,-2);
	v3 = Point(0,2,-2);
}

Triangle::Triangle(Point p1, Point p2, Point p3)
{
	v1 = p1;
	v2 = p2;
	v3 = p3;
}

Normal Triangle::normal()
{
	Vector vec1 = v2 - v1;
	Vector vec2 = v3 - v1;
	//can't implement a cross product function in Vector class that returns a Normal
	//probably because Vector and Normal will include each other

	//cross product between vec1 and vec2
	return Normal(vec1.y*vec2.z - vec1.z*vec2.y, vec1.z*vec2.x - vec1.x*vec2.z, vec1.x*vec2.y - vec1.y*vec2.x);
}

Triangle::~Triangle(void)
{
}
