#include "Camera.h"
#include <math.h>

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

	float normalX = sample.x / myWidth;
	float normalY = sample.y / myHeight;

	float remapX = 2 * normalX - 1;
	float remapY = 1 - 2 * normalY;

	//account for aspect ratio and dof; not sure if needed
	/*
	float ar = myWidth / myHeight;
	float alpha = 2 * atan(abs(myUL.y) / abs(myUL.z));

	float cameraX = (2 * remapX - 1) * ar * tan(alpha/2);
	float cameraY = (1 - 2 * remapY) * tan(alpha/2);
	*/

	Point camSpace = Point(remapX, remapY, -1);
	Vector dir = camSpace - myPos;
	dir.normalize();

	*ray = Ray(myPos, dir, 1, 10);
}

