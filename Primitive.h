#ifndef SHAPE
#define SHAPE

#include "Ray.h"
#include "LocalGeo.h"
#include "BRDF.h"

using namespace std;

class Primitive {

	virtual bool intersect(Ray& ray, float* thit, LocalGeo* local) = 0;
	virtual bool intersectP(Ray& ray) = 0;
	virtual void getBRDF(LocalGeo& local, BRDF* brdf) = 0;
};

#endif