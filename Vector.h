#ifndef VECTOR
#define VECTOR

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
};



#endif