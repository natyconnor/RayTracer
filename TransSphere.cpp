#include "TransSphere.h"


TransSphere::TransSphere(void)
{
	center = Point(0,0,-2);
	radius = 1.0f;
	myBRDF = BRDF();
	t = Transform();
}

TransSphere::TransSphere(Point c, float r, BRDF color, Transform trans){
	center = c;
	radius = r;
	myBRDF = color;
	t = trans;
}

bool TransSphere::isTransformed(){
	return true;
}
Transform TransSphere::getTrans(){
	return t;
}

TransSphere::~TransSphere(void)
{
}


bool TransSphere::intersect(Ray& ray, float* thit, LocalGeo* local)
{
	//transform ray
	Ray origRay = ray;
	ray = t.inverse(ray);

	//call super's intersect with transformed ray
	float tos;
	LocalGeo localos;
	bool returnVal = Sphere::intersect(ray, &tos, &localos);

	//transform returned values from objToWorld space
	*local = t * localos;
	*thit = tos;
	//ray = origRay;

	return returnVal;
}