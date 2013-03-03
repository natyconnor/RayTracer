#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(void)
{
	dir = Vector(1,1,-1);
	myColor =  Color(1,1,1);
}

DirectionalLight::DirectionalLight(Vector d, Color color){
	dir = d;
	myColor = color;
}

DirectionalLight::~DirectionalLight(void)
{
}

void DirectionalLight::generateLightRay(LocalGeo& local, Ray* lray, Color* lcolor){
	Vector rayDir = dir * -1;
	rayDir.normalize();
	*lray = Ray(local.pos, rayDir, 0.1, 100);
	*lcolor = myColor;
}