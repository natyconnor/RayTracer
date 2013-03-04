#include "Normal.h"
#include <math.h>

Normal::Normal(void)
{
	x = 0;
	y = 0;
	z = 0;
}

Normal::Normal(float a, float b, float c){
	x = a;
	y = b;
	z = c;
	normalize();
}

Normal::~Normal(void)
{
}

void Normal::normalize(){
	float mag = sqrt((x*x) + (y*y) + (z*z));
	if(mag != 0.0f){
		x = x / mag;
		y = y / mag;
		z = z / mag;
	}
}

Vector Normal::operator*(float scalar){
	return Vector(x * scalar, y * scalar, z * scalar);
}

float Normal::dot(Vector other){
	return x * other.x + y * other.y + z * other.z;
}

float Normal::dot(Point other){
	return x * other.x + y * other.y + z * other.z;
}