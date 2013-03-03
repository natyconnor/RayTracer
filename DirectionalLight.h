#ifndef DIRLIGHT
#define DIRLIGHT

#include "Vector.h"
#include "Light.h"
class DirectionalLight : public Light
{
public:
	Vector dir;
	Color myColor;

	DirectionalLight(void);
	DirectionalLight(Vector d, Color myColor);
	~DirectionalLight(void);

	void generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor);
};

#endif