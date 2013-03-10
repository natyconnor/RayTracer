#ifndef MATRIX
#define MATRIX

#include "Point.cpp"
#include "Vector.h"
#include "Normal.h"
#include "LocalGeo.h"

class Matrix
{
public:
	float mat[4][4];
	char type;

	Matrix(void);
	Matrix(char type, float x, float y, float z);
	Matrix(float x, float y, float z, float angle);
	~Matrix(void);

	Point operator*(Point other);
	Vector operator*(Vector other);
	Normal operator*(Normal other);
	LocalGeo operator*(LocalGeo other);

	Matrix operator*(Matrix& other);

	void makeInverse();
	void makeTranspose();
	void makeIdentity();
	void print();
};

#endif