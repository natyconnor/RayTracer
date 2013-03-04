#ifndef RAYTRACER
#define RAYTRACER

#include "Ray.h"
#include "Color.cpp"
#include "Primitive.h"
#include "Sphere.h"
#include "PointLight.h"
#include "Triangle.h"
#include "DirectionalLight.h"

#include <vector>

class RayTracer
{
public:
	int threshold;

	vector<Primitive*> prims;
	vector<Light*> lights;
	Point eyePos;

	RayTracer(void);
	RayTracer(int thresh, Point eye);
	~RayTracer(void);

	void trace(Ray& ray, int depth, Color* color);
	Color shading(LocalGeo point, BRDF brdf, Ray lray, Color lcolor);
	void addPrim(Primitive* prim);
	void addLight(Light* l);
};

#endif