#ifndef POINTLIGHT
#define POINTLIGHT

#include "Point.cpp"
#include "Color.cpp"
#include "LocalGeo.h"
#include "Ray.h"

class PointLight
{
public:
	Point myPos;
	Color myColor;

	PointLight(void);
	PointLight(Point pos, Color color);
	~PointLight(void);

	void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor);
};

#endif