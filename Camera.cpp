#include "Camera.h"
#define _USE_MATH_DEFINES

#include <math.h>

Camera::Camera(void)
{
	pos = Point();
}

/*Camera::Camera(Point pos, Point LL, Point UL, Point UR, Point LR, int height, int width)
{
	myPos = pos;
	myLL = LL;
	myUL = UL;
	myUR = UR;
	myUL = UL;
	myWidth = width;
	myHeight = height;
}*/

Camera::Camera(Point lookfrom, Point lookatpoint, Vector u, float fieldOfView, int width, int height){
	pos = lookfrom;
	lookat = lookatpoint;
	up = u;
	fov = fieldOfView;
	pixWidth = width;
	pixHeight = height;
}



Camera::~Camera(void)
{
}

void Camera::generateRay(Sample& sample, Ray* ray){

	/*float normalX = sample.x / myWidth;
	float normalY = sample.y / myHeight;

	float remapX = 2 * normalX - 1;
	float remapY = 2 * normalY - 1;*/

	//account for aspect ratio and dof; not sure if needed
	/*
	float ar = myWidth / myHeight;
	float alpha = 2 * atan(abs(myUL.y) / abs(myUL.z));

	float cameraX = (2 * remapX - 1) * ar * tan(alpha/2);
	float cameraY = (1 - 2 * remapY) * tan(alpha/2);
	*/


	// Calculate ray with camera data given by input file, not four corners /////////////////////
	Vector dir = lookat-pos;
    dir.normalize();
    //cout << n.x << " " << n.y << " " << n.z << endl; //0 0 -1
    Vector u = dir.cross(up);
    u.normalize();
    //cout << u.x << " " << u.y << " " << u.z << endl; //1 0 0
    Vector v = u.cross(dir);
    v.normalize();
    //cout << v.x << " " << v.y << " " << v.z << endl; //0 1 0
 
    Vector xinc = u*2*tan(fov*M_PI/180/2)/(float)pixWidth;
    //cout << xinc.x << " " << xinc.y << " " << xinc.z << endl;
    Vector yinc = v*2*tan(fov*M_PI/180/2)/(float)pixHeight;
    //cout << yinc.x << " " << yinc.y << " " << yinc.z << endl;

    Vector vec = dir + yinc*0.5*(2*sample.y+1-(float)pixHeight) + xinc*0.5*(2*sample.x+1-(float)pixWidth);
    //cout << vec.x << " " << vec.y << " " << vec.z << endl;
    /*if (pixWidth > pixHeight)
    {
            vec.x = vec.x*((float)pixWidth/pixHeight);
    }
	else if(pixHeight > pixWidth)
    {
            vec.y = vec.y*((float)pixHeight/pixWidth);
    }*/
	vec.x = vec.x*pixWidth/pixHeight;
    vec.normalize();
    //cout << vec.x << " " << vec.y << " " << vec.z << endl;
 
    *ray = Ray(pos, vec, 1, 100);
	///////////////////////////////////////////////////////////////////////////////////////////



	/*Point camSpace = Point(remapX, remapY, -3);
	Vector dir = camSpace - myPos;
	dir.normalize();

	*ray = Ray(myPos, dir, 1, 100);*/
}

