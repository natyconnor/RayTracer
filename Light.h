#ifndef LIGHT
#define LIGHT

#include "Color.cpp"
#include "LocalGeo.h"
#include "Ray.h"

class Light
{
public:

	virtual void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) = 0;
};

#endif