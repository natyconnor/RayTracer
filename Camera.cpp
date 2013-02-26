#include "Camera.h"


Camera::Camera(void)
{
	myPos = Point();
}

Camera::Camera(Point pos, Point LL, Point UL, Point UR, Point LR, int height, int width)
{
	myPos = pos;
	myLL = LL;
	myUL = UL;
	myUR = UR;
	myUL = UL;
	myWidth = width;
	myHeight = height;
}


Camera::~Camera(void)
{
}

void Camera::generateRay(Sample& sample, Ray* ray){
	float u = myLL.x + (myLR.x - myLL.x) * (sample.x / myWidth);
	float v = myUL.y + (myLL.y - myUL.y) * (sample.y / myHeight);
	float w = -1; //for now image plane is always at z = -1

	*ray = Ray(myPos, Point(u, v, w) - myPos, 1, 10);
}

