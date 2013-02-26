#include "RayTracer.h"


RayTracer::RayTracer(void)
{
	threshold = 10;
}

RayTracer::RayTracer(int thresh){
	threshold = thresh;
}


RayTracer::~RayTracer(void)
{
}


void RayTracer::trace(Ray& ray, int depth, Color* color){
	if(depth > threshold){
		*color = Color();
	}
	//loop through all primitives
	//for(int i = 0; i < prims.size(); i++){
		//if intersection
		//compute necessary info
	//}

	//compute shading

}
