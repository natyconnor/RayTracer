#ifndef defBRDF
#define defBRDF

#include "Color.cpp"
class BRDF
{
public:
	Color kd, ks, ka, kr;

	BRDF(void);
	BRDF(Color diff, Color spec, Color amb, Color ref);
	~BRDF(void);
};

#endif