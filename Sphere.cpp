#include "Sphere.h"


Sphere::Sphere(void)
{
	center = Point();
	radius = 1.0;
}

Sphere::Sphere(Point cen, float rad)
{
	center = cen;
	radius = rad;
}

bool Sphere::intersect(Ray& ray, float* thit, LocalGeo* local){
	return false;
}

bool Sphere::intersectP(Ray& ray){
	return false;
}

void Sphere::getBRDF(LocalGeo& local, BRDF* brdf){
	int y = 1;
}


Sphere::~Sphere(void)
{
}
