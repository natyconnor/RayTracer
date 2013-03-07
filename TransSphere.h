#ifndef TRANSSPHERE_H
#define TRANSSPHERE_H

#include "Sphere.h"
#include <vector>
#include "Transform.h"

using namespace std;

class TransSphere : public Sphere
{
public:
	float radius;
	Point center;
	BRDF myBRDF;
	vector<Transform>* transforms;

	TransSphere(Point p, float rad, BRDF brdf, vector<Transform>* transformations);
	bool intersect(Ray& ray, float *thit, LocalGeo* local);
	void getBRDF(LocalGeo& local, BRDF* brdf);
	bool isTransformed();
	vector<Transform> getTrans();
};
#endif