#ifndef RAY
#define RAY

#include "Point.cpp"
#include "Vector.h"
class Ray
{
public:
	Point pos;
	Vector dir;
	float t_min, t_max;

	Ray(void);
	Ray(Point position, Vector direction, float min, float max);
	Ray(Point position, Vector direction, float min, float max, bool normalize);
	~Ray(void);
};

#endif