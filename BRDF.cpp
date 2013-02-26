#include "BRDF.h"


BRDF::BRDF(void)
{
	kd = Color();
	ks = Color();
	ka = Color();
	kr = Color();
}

BRDF::BRDF(Color diff, Color spec, Color amb, Color ref)
{
	kd = diff;
	ks = spec;
	ka = amb;
	kr = ref;
}


BRDF::~BRDF(void)
{
}
