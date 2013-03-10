#include "Triangle.h"


Triangle::Triangle(void)
{
	v1 = Point(-1,0,-2);
	v2 = Point(1,0,-2);
	v3 = Point(0,2,-2);
	myBRDF = BRDF();
}

Triangle::Triangle(Point p1, Point p2, Point p3, BRDF brdf)
{
	v1 = p1;
	v2 = p2;
	v3 = p3;
	myBRDF = brdf;
}

Normal Triangle::normal()
{
	Vector vec1 = v2 - v1;
	Vector vec2 = v3 - v1;


	//can't implement a cross product function in Vector class that returns a Normal
	//probably because Vector and Normal will include each other
	//cross product between vec1 and vec2

	return Normal(vec1.y*vec2.z - vec1.z*vec2.y, vec1.z*vec2.x - vec1.x*vec2.z, vec1.x*vec2.y - vec1.y*vec2.x);
}

bool Triangle::intersect(Ray& ray, float* thit, LocalGeo* local){
	/*Geometric solution*/
	Normal n = normal();

	//check if ray and triangle are parallel
	if(n.dot(ray.dir) == 0)
		return false;
	//compute D of plane equation
	float d = n.dot(v1);

	//with equation of ray and equation of plane, we can calculate thit
	float t = -(n.dot(ray.pos) + d) / (n.dot(ray.dir));

	//check if triangle is not within ray's length
	if(t < ray.t_min || t > ray.t_max)
		return false;

	Point p = ray.pos + (ray.dir * t);

	//Now with point intersecting plane, use inside out test
	//to see if it's in the triangle
	Vector c;

	//edge 1
	Vector edge1 = v2 - v1;
	Vector vp1 = p - v1;
	c = edge1.cross(vp1);
	//c = vp1.cross(edge1);
	if(n.dot(c) < 0)
		return false; //p is on the wrong side of the edge

	//edge 2
	Vector edge2 = v3 - v2;
	Vector vp2 = p - v2;
	c = edge2.cross(vp2);
	//c = vp2.cross(edge2);
	if(n.dot(c) < 0)
		return false; //p is on the wrong side of the edge

	//edge 3
	Vector edge3 = v1 - v3;
	Vector vp3 = p - v3;
	c = edge3.cross(vp3);
	//c = vp3.cross(edge3);
	if(n.dot(c) < 0)
		return false; //p is on the wrong side of the edge

	*thit = t;
	*local = LocalGeo(p, n);
	return true;
}

bool Triangle::intersectP(Ray& ray){
	float dummyt;
	LocalGeo dummyGeo;
	return intersect(ray, &dummyt, &dummyGeo);
}

void Triangle::getBRDF(LocalGeo& local, BRDF* brdf){
	*brdf = myBRDF;
}

Triangle::~Triangle(void)
{
}
