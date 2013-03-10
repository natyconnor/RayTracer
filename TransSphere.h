#ifndef TRANSSPHERE
#define TRANSSPHERE

#include "Sphere.h"
#include "Transform.h"

class TransSphere : public Sphere
{
public:
	Transform t;

	TransSphere(void);
	TransSphere(Point center, float radius, BRDF color, Transform trans);
	~TransSphere(void);

	bool isTransformed();
	Transform getTrans();

	bool intersect(Ray& ray, float* thit, LocalGeo* local);
};

#endif