#include "Ray.h"


Ray::Ray()
{
	pos = Point();
	dir = Vector();
	t_min = 0;
	t_max = 0;
}

Ray::Ray(Point position, Vector direction, float min, float max)
{
	pos = position;
	dir = direction;
	t_min = min;
	t_max = max;
}


Ray::~Ray(void)
{
}
