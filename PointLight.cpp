#include "PointLight.h"


PointLight::PointLight(void)
{
	myPos = Point();
	myColor = Color(1,1,1);
}

PointLight::PointLight(Point pos, Color color){
	myPos = pos;
	myColor = color;
}

void PointLight::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor) {
	Vector rayDir = myPos - local.pos;
	rayDir.normalize();
	*lray = Ray(local.pos, rayDir, 0.5, 10);
	*lcolor = myColor;
}


PointLight::~PointLight(void)
{
}
