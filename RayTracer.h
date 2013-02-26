#ifndef RAYTRACER
#define RAYTRACER

#include "Ray.h"
#include "Color.cpp"
#include "Primitive.h"

class RayTracer
{
public:
	int threshold;
	

	RayTracer(void);
	RayTracer(int thresh);
	~RayTracer(void);

	void trace(Ray& ray, int depth, Color* color);
};

#endif