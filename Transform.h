#ifndef TRANSFORM
#define TRANSFORM

#include "Matrix.h"
#include "Point.cpp"
#include "Vector.h"
#include "Normal.h"
#include "LocalGeo.h"
#include "Ray.h"

#include <vector>

using namespace std;

class Transform
{
public:
	Matrix m, mInverse;
	Matrix r, rInverse;
	Matrix n;

	Transform(void);
	Transform(vector<Matrix> matrices);
	~Transform(void);

	void addMatrix(Matrix m);

	Point operator*(Point other);
	Vector operator*(Vector other);
	Normal operator*(Normal other);
	LocalGeo operator*(LocalGeo other);
	Ray operator*(Ray other);

	Point inverse(Point other);
	Vector inverse(Vector other);
	//Normal inverse(Normal other);
	LocalGeo inverse(LocalGeo other);
	Ray inverse(Ray other);
};

#endif