#ifndef SHAPE
#define SHAPE

#include "Ray.h"
#include "LocalGeo.h"
#include "BRDF.h"
#include "Transform.h"
#include <vector>

using namespace std;

class Primitive {
public:
	virtual bool intersect(Ray& ray, float* thit, LocalGeo* local) = 0;
	virtual bool intersectP(Ray& ray) = 0;
	virtual void getBRDF(LocalGeo& local, BRDF* brdf) = 0;

	virtual bool isTransformed() = 0;
	virtual vector<Transform> getTrans() = 0;
};

#endif