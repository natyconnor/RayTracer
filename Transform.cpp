#include "Transform.h"

Transform::Transform()
{
	transforms = vector<Matrix>();
	nTransforms = vector<Matrix>();
}

void Transform::addTranslate(float x, float y, float z)
{
	transforms.push_back(Matrix("translate", x, y, z));
	nTransforms.push_back(Matrix("translate",-x, -y, -z));
}

void Transform::addRotate(float x, float y, float z, float degrees)
{
	transforms.push_back(Matrix(x, y, z, degrees));
	nTransforms.push_back(Matrix(x, y, z, -degrees));
}

void Transform::addScale(float x, float y, float z)
{
	transforms.push_back(Matrix("scale", x, y, z));
	nTransforms.push_back(Matrix("scale", 1/x, 1/y, 1/z));
}

void Transform::print()
{
	for (int i = 0; i < transforms.size(); i++)
	{
		transforms.at(i).print();
	}
}