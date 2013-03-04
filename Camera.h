#ifndef CAMERA
#define CAMERA

#include "Sample.cpp"
#include "Ray.h"

class Camera
{
public:
	Point pos, lookat;
	Vector up;
	float fov;
	//Point myLL, myUL, myUR, myLR;
	int pixWidth, pixHeight;

	Camera(void);
	Camera(Point pos, Point LL, Point UL, Point UR, Point LR, int height, int width);
	Camera(Point lookfrom, Point lookatpoint, Vector up, float fieldOfView, int width, int height);
	~Camera(void);

	void generateRay(Sample& sample, Ray* ray);
};

#endif