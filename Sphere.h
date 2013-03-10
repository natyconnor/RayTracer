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
	BRDF myBRDF;



	Sphere(void);
	Sphere(Point cen, float rad, BRDF brdf);
	~Sphere(void);

	bool isTransformed();

	bool intersect(Ray& ray, float* thit, LocalGeo* local);
	bool intersectP(Ray& ray);
	void getBRDF(LocalGeo& local, BRDF* brdf);
};

#endif