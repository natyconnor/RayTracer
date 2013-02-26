#ifndef RAYTRACER
#define RAYTRACER

#include "Ray.h"
#include "Color.cpp"
#include "Primitive.h"
#include "Sphere.h"

#include <vector>


class RayTracer
{
public:
	int threshold;

	vector<Sphere> prims;

	RayTracer(void);
	RayTracer(int thresh);
	~RayTracer(void);

	void trace(Ray& ray, int depth, Color* color);
};

#endif