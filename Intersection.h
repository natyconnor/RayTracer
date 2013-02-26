#ifndef INTERSECTION
#define INTERSECTION

#include "LocalGeo.h"
#include "Primitive.h"

using namespace std;

class Intersection {
public:
	LocalGeo localGeo;
	Primitive* shape;

	Intersection(void);
	Intersection(LocalGeo lg, Primitive* shp);
	~Intersection(void);
};

#endif