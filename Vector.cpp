#include "Vector.h"

#include <cmath>


Vector::Vector(void)
{
	x = 0;
	y = 0;
	z = 0;
}

Vector:: Vector(float a, float b, float c)
{
	x = a;
	y = b;
	z = c;
}

Vector Vector::operator+(Vector other){
	return Vector(x + other.x, y + other.y, z + other.z);
}

Vector Vector::operator-(Vector other){
	return Vector(x - other.x, y - other.y, z - other.z);
}

Vector Vector::operator*(float scalar){
	return Vector(scalar * x, scalar * y, scalar * z);
}

Vector Vector::operator/(float scalar){
	return Vector(x / scalar, y / scalar, z / scalar);
}

void Vector::normalize(){
	float mag = sqrt((x*x) + (y*y) + (z*z));
	if(mag != 0.0){
		x = x / mag;
		y = y / mag;
		z = z / mag;
	}
}

float Vector::dot(Vector other){
	return x * other.x + y * other.y + z * other.z;
}

Vector::~Vector(void)
{
}
