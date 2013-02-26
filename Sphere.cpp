#include "Sphere.h"
#include <math.h>

Sphere::Sphere(void)
{
	center = Point(0, 0, -3);
	radius = 2.0;
}

Sphere::Sphere(Point cen, float rad)
{
	center = cen;
	radius = rad;
}

bool Sphere::intersect(Ray& ray, float* thit, LocalGeo* local){
	//|R(t) - C|^2 r^2 = 0
	//|pos + tdir - center|^2 - r^2 = 0

	/* Geometric solution

	Vector L = center - ray.pos; //vector from origin of ray to center of sphere, making hypoteneuse of right triangle
	Vector r = ray.dir;
	r.normalize();
	float tca = L.dot(r); // t value  of ray parallel to center of sphere
	if(tca < 0)
		return false;

	//d will be opposite side of L,tca right triangle
	//d^2 + tca^2 = L^2
	float d = sqrt((L.dot(L)) - (tca * tca));
	if(d < 0 || d > radius)
		return false;

	//d makes another right triangle with radius and t value thc
	//d^2 + thc^2 = radius^2
	float thc = sqrt(radius*radius - d*d);

	float t0 = tca - thc;
	float t1 = tca + thc;

	//it's finding an intersect for every single pixel. Find out why
	if(t0 > 0 && t1 > 0){
		//successful intersection
		//find the closer one
		if(t0 < t1){
			*thit = t0;
			//need to calculate normal
			*local = LocalGeo(ray.pos+(r*t0), Normal());
		}
		else{
			*thit = t1;
			*local = LocalGeo(ray.pos+(r*t1), Normal());
		}
		return true;
	}

	return false;

	*/

	/*Analytic Solution*/
	Vector L = ray.pos - center;
	Vector r = ray.dir;
	r.normalize();
	float a = r.dot(r);
	float b = 2 * r.dot(L);
	float c = L.dot(L) - (radius*radius);

	//quadratic equation
	float t0, t1;
	float discr = b * b - 4 * a * c;
	if(discr < 0)
		return false;
	else if(discr == 0){
		t0 = t1 = -0.5 * b / a;
	} else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		t0 = q / a;
		t1 = c / q;
	}
	return true;
}

bool Sphere::intersectP(Ray& ray){
	return false;
}

void Sphere::getBRDF(LocalGeo& local, BRDF* brdf){
	*brdf = BRDF();
}


Sphere::~Sphere(void)
{
}
