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
	prims.push_back(Sphere(Point(0.4,0.4,-2), 0.3, BRDF(Color(1,0,0), Color(1,1,1), Color(0.05,0,0),Color())));
	prims.push_back(Sphere(Point(-0.5,-0.5,-3), 0.7, BRDF(Color(0,1,0), Color(1,1,1), Color(0,0.05,0),Color())));
	prims.push_back(Sphere(Point(-0.7,-0.7,-2), 0.2, BRDF(Color(0,0.4,0.7), Color(0.8,0.8,1), Color(0,0,0.05),Color())));
	lights.push_back(PointLight(Point(10,10,0), Color(1,1,1)));
	lights.push_back(PointLight(Point(-5,-3,0), Color(1,1,1)));
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
		if(prims.at(i).intersect(ray, &thit, &intersection)){
			//keep track of the closest intersection to the camera, since that is what we will draw
			//float dist = (intersection.pos - eyePos).magnitude();
			if(thit < minDistance){
				minDistance = thit;
				minPrimIndex = i;
				closestInter = intersection;
			}
		}
	}
	//compute shading
	if(minPrimIndex != -1){
		Sphere closest = prims.at(minPrimIndex);
		Ray lray = Ray();
		Color lcolor = Color();
		BRDF brdf = BRDF();
		closest.getBRDF(closestInter, &brdf);
		*color = brdf.ka;

		for(int i = 0; i < lights.size(); i++){
			lights.at(i).generateLightRay(closestInter, &lray, &lcolor);

			//check for intersection with primitives for shadows
			bool isShadow = false;
			for(int j = 0; j < prims.size(); j++){
				if(j != minPrimIndex && prims.at(j).intersectP(lray)){
					isShadow = true;
					break;
				}
			}

			if(!isShadow){
				//calculate Phong stuff
				*color = *color + shading(closestInter, brdf, lray, lcolor);
				//*color = Color(1,0,0);
			}
		}
	}
}

Color RayTracer::shading(LocalGeo point, BRDF brdf, Ray lray, Color lcolor){
	//diffuse component
	//dot product between normal and light vectors
	float diff = point.norm.dot(lray.dir);

	//specular component
	Vector v = eyePos - point.pos;
	v.normalize();
	Vector r = (lray.dir * -1) + (point.norm * (2 * diff));
	r.normalize();
	float spec = r.dot(v);

	return (lcolor * brdf.kd) * max(diff,0.0f) + (lcolor * brdf.ks) * pow(max(spec,0.0f),5);
}
