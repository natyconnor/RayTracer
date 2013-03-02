#ifndef TRIANGLE
#define TRIANGLE

#include "Point.cpp"
#include "Normal.h"
#include "Primitive.h"

class Triangle : public Primitive
{
public:
	Point v1,v2,v3;

	Triangle(void);
	Triangle(Point p1, Point p2, Point p3);
	~Triangle(void);

	Normal normal();
};

#endif