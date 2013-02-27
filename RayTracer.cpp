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
	LocalGeo closestInter;
	float minDistance = 99999;
	int minPrimIndex = -1;
	//loop through all primitives
	for(int i = 0; i < prims.size(); i++){
		//if intersection
		if(!prims.at(i).intersect(ray, &thit, &intersection)){
			return;
		}
		//keep track of the closest intersection to the camera, since that is what we will draw
		float dist = (intersection.pos - eyePos).magnitude();
		if(dist < minDistance){
			minDistance = dist;
			minPrimIndex = i;
			closestInter = intersection;
		}
	}
	//compute shading
	if(minPrimIndex != -1){
		Sphere closest = prims.at(minPrimIndex);
		Ray lray = Ray();
		Color lcolor = Color();
		BRDF brdf = BRDF();
		closest.getBRDF(closestInter, &brdf);
		for(int i = 0; i < lights.size(); i++){
			lights.at(i).generateLightRay(closestInter, &lray, &lcolor);

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

	//specular component
	Vector v = point.pos - eyePos;
	v.normalize();
	Vector r = (lray.dir * -1) + (point.norm * (2 * diff));
	r.normalize();
	float spec = r.dot(v);

	return brdf.ka + (lcolor * brdf.kd) * max(diff,0.0f) + (lcolor * brdf.ks) * pow(max(spec,0.0f),20);
}
