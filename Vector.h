#ifndef VECTOR
#define VECTOR

//#include "Normal.h"

class Vector
{
public:
	float x, y, z;

	Vector(void);
	Vector(float a, float b, float c);
	~Vector(void);

	Vector operator + (Vector);
	Vector operator - (Vector);
	Vector operator * (float);
	Vector operator / (float);

	void normalize();
	float magnitude();
	float dot(Vector other);
	//Normal cross(Vector other);
};



#endif