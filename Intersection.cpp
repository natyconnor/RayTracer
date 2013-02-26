#include "Intersection.h"

#include "Sphere.h"

Intersection::Intersection(void)
{
	localGeo = LocalGeo();
	shape = &Sphere();
}


Intersection::~Intersection(void)
{
}

Intersection::Intersection(LocalGeo lg, Primitive* shp){
	localGeo = lg;
	shape = shp;
}
