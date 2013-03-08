#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "Point.cpp"
#include "Vector.h"
#include "Normal.h"

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
	Normal operator*(Normal n);
	void transpose();
	void print();
};
#endif