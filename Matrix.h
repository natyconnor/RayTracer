#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "Point.cpp"
#include "Vector.h"

using namespace std;

class Matrix
{
public:
	Matrix();
	Matrix(string transform, float x, float y, float z);
	Matrix(float x, float y, float z, float angle);
	float mat[4][4];
	Point operator*(Point p);
	Vector operator*(Vector vec);
	void print();
};
#endif