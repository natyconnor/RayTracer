#include "RayTracer.h"
#include "Point.cpp"

RayTracer::RayTracer(void)
{
	threshold = 10;
	prims.push_back(Sphere());
	eyePos = Point(0, 0, 0);
}

RayTracer::RayTracer(int thresh, Point eye){
	threshold = thresh;
	prims.push_back(Sphere());
	lights.push_back(PointLight(Point(-1.5,0,-2), Color(1,1,1)));
	eyePos = eye;
}


RayTracer::~RayTracer(void)
{
}


void RayTracer::trace(Ray& ray, int depth, Color* color){
	if(depth > threshold){
		*color = Color();
	}

	*color = Color();
	float thit;
	LocalGeo intersection;
	float minDistance = 99999;
	int minPrimIndex = -1;
	//loop through all primitives
	for(int i = 0; i < prims.size(); i++){
		//if intersection
		if(!prims.at(i).intersect(ray, &thit, &intersection)){
			return;
		}
		//compute necessary info
		float dist = (intersection.pos - eyePos).magnitude();
		if(dist < minDistance){
			minDistance = dist;
			minPrimIndex = i;
		}
	}
	//compute shading
	if(minPrimIndex != -1){
		Sphere closest = prims.at(minPrimIndex);
		Ray lray = Ray();
		Color lcolor = Color();
		BRDF brdf = BRDF();
		closest.getBRDF(intersection, &brdf);
		for(int i = 0; i < lights.size(); i++){
			lights.at(i).generateLightRay(intersection, &lray, &lcolor);

			//calculate Phong stuff
			*color = *color + shading(intersection, brdf, lray, lcolor);
			//*color = Color(1,0,0);
		}
	}
}

Color RayTracer::shading(LocalGeo point, BRDF brdf, Ray lray, Color lcolor){
	//diffuse component
	//dot product between normal and light vectors
	float diff = point.norm.dot(lray.dir);

	return brdf.ka + (lcolor * brdf.kd) * max(diff,0.0f);
}
