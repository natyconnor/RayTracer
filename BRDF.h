#ifndef defBRDF
#define defBRDF

#include "Color.cpp"
class BRDF
{
public:
	Color kd, ks, ka, kr;
	float sp;

	BRDF(void);
	BRDF(Color diff, Color spec, Color amb, Color ref, float power);
	~BRDF(void);
};

#endif