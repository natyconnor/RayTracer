#ifndef TRIANGLE
#define TRIANGLE

#include "Point.cpp"
#include "Normal.h"
#include "Primitive.h"

class Triangle : public Primitive
{
public:
	Point v1,v2,v3;
	BRDF myBRDF;

	Triangle(void);
	Triangle(Point p1, Point p2, Point p3, BRDF brdf);
	~Triangle(void);

	bool intersect(Ray& ray, float* thit, LocalGeo* local);
	bool intersectP(Ray& ray);
	void getBRDF(LocalGeo& local, BRDF* brdf);

	Normal normal();
};

#endif