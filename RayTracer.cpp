#include "RayTracer.h"
#include "Point.cpp"

RayTracer::RayTracer(void)
{
	threshold = 10;
	prims.push_back(Sphere());
}

RayTracer::RayTracer(int thresh){
	threshold = thresh;
	prims.push_back(Sphere());
}


RayTracer::~RayTracer(void)
{
}


void RayTracer::trace(Ray& ray, int depth, Color* color){
	if(depth > threshold){
		*color = Color();
	}
	//loop through all primitives
	for(int i = 0; i < prims.size(); i++){

		float thit;
		LocalGeo intersection;
		//if intersection
		if(!prims.at(i).intersect(ray, &thit, &intersection)){
			*color = Color(0, 0, 1);
			return;
		}
		//compute necessary info
		*color = Color(1, 0, 0) + Color(0, 1, 0);
	}

	//compute shading

}
