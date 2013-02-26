#ifndef NORMAL
#define NORMAL

class Normal
{
public:
	float x, y, z;

	Normal(void);
	Normal(float a, float b, float c);
	~Normal(void);

	Normal operator + (Normal);
	Normal operator - (Normal);
};

#endif