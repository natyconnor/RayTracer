#include "BRDF.h"


BRDF::BRDF(void)
{
	kd = Color();
	ks = Color();
	ka = Color();
	kr = Color();
	sp = 20.0;
}

BRDF::BRDF(Color diff, Color spec, Color amb, Color ref, float power)
{
	kd = diff;
	ks = spec;
	ka = amb;
	kr = ref;
	sp = power;
}


BRDF::~BRDF(void)
{
}
