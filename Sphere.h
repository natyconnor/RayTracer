#ifndef SPHERE
#define SPHERE

#include "Primitive.h"
#include "Point.cpp"
#include "Ray.h"
#include "LocalGeo.h"
#include "BRDF.h"

using namespace std;

class Sphere: public Primitive
{
public:
	Point center;
	float radius;

	Sphere(void);
	Sphere(Point cen, float rad);
	~Sphere(void);

	bool intersect(Ray& ray, float* thit, LocalGeo* local);
	bool intersectP(Ray& ray);
	void getBRDF(LocalGeo& local, BRDF* brdf);
};

#endif