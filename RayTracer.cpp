#include "RayTracer.h"
#include "Point.cpp"

RayTracer::RayTracer(void)
{
	threshold = 10;
	//prims.push_back(Sphere());
	eyePos = Point(0, 0, 0);
}

RayTracer::RayTracer(int thresh, Point eye){
	threshold = thresh;

	Sphere* sph1 = new Sphere(Point(0,0,-20), 3.0, BRDF(Color(1,0,1), Color(1,1,1), Color(0.1,0.1,0.1), Color(), 50));
	Sphere* sph2 = new Sphere(Point(-2,2,-15), 1.0, BRDF(Color(1,1,0), Color(1,1,1), Color(0.1,0.1,0.1), Color(), 50));
	Sphere* sph3 = new Sphere(Point(-2,-2,-15), 1.0, BRDF(Color(0,1,1), Color(1,1,1), Color(0.1,0.1,0.1), Color(), 50));
	Triangle* tri = new Triangle(Point(5,5,-17), Point(1,4,-20), Point(6,-1,-20), BRDF(Color(0.1,0.1,0.1), Color(1,1,1), Color(0.1,0.1,0.1), Color(1,1,1), 50));
	
	prims.push_back(tri);
	prims.push_back(sph1);
	prims.push_back(sph2);
	prims.push_back(sph3);

	DirectionalLight* dl1 = new DirectionalLight(Vector(0.57735027, -0.57735027, -0.57735027), Color(1,1,1));
	DirectionalLight* dl2 = new DirectionalLight(Vector(0.57735027, 0.57735027, -0.57735027), Color(0,0,1));
	lights.push_back(dl1);
	lights.push_back(dl2);
	eyePos = eye;
}


RayTracer::~RayTracer(void)
{
}


void RayTracer::trace(Ray& ray, int depth, Color* color){
	if(depth > threshold){
		return;
	}

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


		Vector rDir = (ray.dir * -1) + (intersection.norm * (2 * intersection.norm.dot(ray.dir)));
		rDir.normalize();
		Ray r = Ray(intersection.pos, rDir, 0.5, ray.t_max);

		for(vector<Light*>::iterator lIter = lights.begin(); lIter != lights.end(); ++ lIter){
			Light* l = *lIter;
			(*l).generateLightRay(closestInter, &lray, &lcolor);

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
				Color refColor = Color();
				trace(r, depth+1, &refColor);
				//calculate Phong stuff
				*color = *color + shading(closestInter, brdf, lray, lcolor) + brdf.kr*refColor;
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

	return (lcolor * brdf.kd) * max(diff,0.0f) + (lcolor * brdf.ks) * pow(max(spec,0.0f),brdf.sp) + brdf.kr;
}
