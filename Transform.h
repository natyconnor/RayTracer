#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Matrix.h"
#include <vector>

class Transform
{
public:
	Transform();
	void addTranslate(float x, float y, float z);
	void addRotate(float x, float y, float z, float degrees);
	void addScale(float x, float y, float z);
	vector<Matrix> transforms;
	void print();
};
#endif