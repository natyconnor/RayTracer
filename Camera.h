#ifndef CAMERA
#define CAMERA

#include "Sample.cpp"
#include "Ray.h"

class Camera
{
public:
	Point myPos;
	Point myLL, myUL, myUR, myLR;
	int myWidth, myHeight;

	Camera(void);
	Camera(Point pos, Point LL, Point UL, Point UR, Point LR, int height, int width);
	~Camera(void);

	void generateRay(Sample& sample, Ray* ray);
};

#endif