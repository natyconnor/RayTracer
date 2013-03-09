#ifndef TRANSTRIANGLE_H
#define TRANSTRIANGLE_H

#include "Triangle.h"
#include <vector>
#include "Transform.h"

class TransTriangle : public Triangle
{
public:
	
	Point v1, v2, v3;
	BRDF myBRDF;

	int x;

	vector<Transform>* transforms;
	vector<Transform> getTrans();

	TransTriangle(Point a, Point b, Point c, BRDF brdf, vector<Transform>* transformations);
	bool intersect(Ray& ray, float *thit, LocalGeo* local);
	bool intersectP(Ray& ray);
	void getBRDF(LocalGeo& local, BRDF* brdf);
	bool isTransformed();

	Normal normal();
};
#endif
