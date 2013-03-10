#include "Transform.h"


Transform::Transform(void)
{
	m = Matrix();
	m.makeIdentity();
	mInverse = Matrix();
	mInverse.makeIdentity();
	r = Matrix();
	r.makeIdentity();
	rInverse = Matrix();
	rInverse.makeIdentity();

	n = Matrix();
	n.makeIdentity();
}

Transform::Transform(vector<Matrix> matrices)
{

}

Transform::~Transform(void)
{
}

void Transform::addMatrix(Matrix newMatrix){
	Matrix copy = newMatrix;
	copy.makeInverse();
	m = newMatrix*m;
	mInverse = mInverse * copy;

	//Ray matrix stuff
	if(newMatrix.type != 't'){
		r = newMatrix*r;
		rInverse = r*copy;
	}

	n = mInverse;
	n.makeTranspose();
}

Point Transform::operator*(Point other){
	return m*other;
}
Vector Transform::operator*(Vector other){
	return m*other;
}
Normal Transform::operator*(Normal other){
	return n*other;
}
LocalGeo Transform::operator*(LocalGeo other){
	return LocalGeo(m*other.pos, n*other.norm);
}
Ray Transform::operator*(Ray other){
	return Ray(r*other.pos, m*other.dir, 0.005, FLT_MAX, false);
}

Point Transform::inverse(Point other){
	return mInverse*other;
}
Vector Transform::inverse(Vector other){
	return mInverse*other;
}
/*Normal Transform::inverse(Normal other){
	return nInverse*other;
}*/
LocalGeo Transform::inverse(LocalGeo other){
	return LocalGeo(mInverse*other.pos, n*other.norm);
}
Ray Transform::inverse(Ray other){
	return Ray(rInverse*other.pos, mInverse*other.dir, 0.005, FLT_MAX, false);
}
