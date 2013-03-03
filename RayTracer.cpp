#include "RayTracer.h"
#include "Point.cpp"

RayTracer::RayTracer(void)
{
	threshold = 100;
	//prims.push_back(Sphere());
	eyePos = Point(0, 0, 0);
}

RayTracer::RayTracer(int thresh, Point eye){
	threshold = thresh;
	//prims.push_back(Sphere(Point(0.4,0.4,-2), 0.3, BRDF(Color(1,0,0), Color(1,1,1), Color(0.05,0,0),Color())));
	//prims.push_back(Sphere(Point(-0.5,-0.5,-3), 0.7, BRDF(Color(0,1,0), Color(1,1,1), Color(0,0.05,0),Color())));
	//prims.push_back(Sphere(Point(-0.7,-0.7,-2), 0.2, BRDF(Color(0,0.4,0.7), Color(0.8,0.8,1), Color(0,0,0.05),Color())));

	Sphere* sph = new Sphere(Point(0,0,-20), 3.0, BRDF(Color(1,0,1), Color(1,1,1), Color(0.1,0.1,0.1), Color()));
	Triangle* tri = new Triangle(Point(0,8,-25), Point(-5,-4,-25), Point(6,-1,-22), BRDF(Color(0,0.4,0.7), Color(0.8,0.8,1), Color(0,0,0.05),Color()));
	//prims.push_back(Triangle(Point(5,8,-17), Point(1,4,-20), Point(6,-1,-20), BRDF(Color(0,0.4,0.7), Color(0.8,0.8,1), Color(0,0,0.05),Color())));
	prims.push_back(tri);
	prims.push_back(sph);

	//lights.push_back(PointLight(Point(10,10,0), Color(1,1,1)));
	lights.push_back(PointLight(Point(-5,-3,0), Color(1,1,1)));
	eyePos = eye;
}


RayTracer::~RayTracer(void)
{
}


void RayTracer::trace(Ray& ray, int depth, Color* color){
	if(depth > threshold){
		*color = Color();
		return;
	}

	*color = Color();
	float thit;
	LocalGeo intersection;
	LocalGeo closestInter;
	float minDistance = 99999;
	Primitive* closest = 0;

	//loop through all primitives
	for(vector<Primitive*>::iterator iter = prims.begin(); iter != prims.end(); ++iter){
		Primitive* s = *iter;
		//if intersection
		if((*s).intersect(ray, &thit, &intersection)){
			//keep track of the closest intersection to the camera, since that is what we will draw
			//float dist = (intersection.pos - eyePos).magnitude();
			if(thit < minDistance){
				minDistance = thit;
				closest = s;
				closestInter = intersection;
			}
		}
	}
	//compute shading
	if(minDistance != 99999){
		Ray lray = Ray();
		Color lcolor = Color();
		BRDF brdf = BRDF();
		(*closest).getBRDF(closestInter, &brdf);
		*color = brdf.ka;

		for(int i = 0; i < lights.size(); i++){
			lights.at(i).generateLightRay(closestInter, &lray, &lcolor);

			//check for intersection with primitives for shadows
			bool isShadow = false;
			for(vector<Primitive*>::iterator iter = prims.begin(); iter != prims.end(); ++iter){
				Primitive* s = *iter;
				if((*s).intersectP(lray)){
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
