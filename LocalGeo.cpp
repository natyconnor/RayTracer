#include "LocalGeo.h"


LocalGeo::LocalGeo(void)
{
	pos = Point();
	norm = Normal();
}

LocalGeo::LocalGeo(Point position, Normal normal)
{
	pos = position;
	norm = normal;
}

LocalGeo::~LocalGeo(void)
{
}
