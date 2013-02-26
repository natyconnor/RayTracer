#ifndef LOCALGEO
#define LOCALGEO

#include "Point.cpp"
#include "Normal.h"

class LocalGeo
{
public:
	Point pos;
	Normal norm;

	LocalGeo(void);
	LocalGeo(Point position, Normal normal);
	~LocalGeo(void);
};

#endif