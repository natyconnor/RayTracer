#ifndef NORMAL
#define NORMAL

#include "Vector.h"
#include "Point.cpp"

class Normal
{
public:
	float x, y, z;

	Normal(void);
	Normal(float a, float b, float c);
	~Normal(void);

	Normal operator + (Normal);
	Normal operator - (Normal);
	Vector operator * (float);
	void normalize();

	float dot(Vector other);
	float dot(Point other);
};

#endif