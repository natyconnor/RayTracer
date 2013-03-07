#include "Vector.h"

#include <cmath>
#include <iostream>

using namespace std;


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
	float mag = magnitude();
	if(mag != 0.0){
		x = x / mag;
		y = y / mag;
		z = z / mag;
	}
}

float Vector::magnitude(){
	return sqrt((x*x) + (y*y) + (z*z));
}

float Vector::dot(Vector other){
	return x * other.x + y * other.y + z * other.z;
}

Vector Vector::cross(Vector other){
	return Vector(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
}

void Vector::print(){
	cout << "[" << x << " " << y << " " << z << "]" << endl;
}

Vector::~Vector(void)
{
}
