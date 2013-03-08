#include "TransSphere.h"

TransSphere::TransSphere(Point p, float rad, BRDF brdf, vector<Transform>* transformations)
{
	center = p;
	radius = rad;
	myBRDF = brdf;
	transforms = transformations;
}

void TransSphere::getBRDF(LocalGeo& local, BRDF* brdf)
{
	*brdf = myBRDF;
}

bool TransSphere::intersect(Ray& ray, float *thit, LocalGeo* local)
{
	Ray newr = Ray(ray.pos, ray.dir, ray.t_min, ray.t_max);
	//cout << "ima sphere" << endl;
	//for each transform
	for (int i = 0 ; i < transforms->size(); i++)
	{
		//for each matrix
		for (int j = 0; j < transforms->at(i).transforms.size(); j++)
		{
			Matrix m = transforms->at(i).transforms.at(j);
			if (m.mat[0][0] == 1 && m.mat[1][1] == 1 && m.mat[2][2] == 1) //translate
			{
				ray.pos = m*ray.pos;
				//ray.dir = m*ray.dir;
			}
			else //scale
			{
				ray.pos = m*ray.pos;
				ray.dir = m*ray.dir;
			}
		}
	}

	/*Analytic Solution*/
	float a = ray.dir.dot(ray.dir);
	float b = 2*(ray.pos - center).dot(ray.dir);
	float c = (ray.pos - center).dot((ray.pos - center)) - radius*radius;
	if (b*b-4.0*a*c < 0)
	{
		ray = newr;
		return false;
	}
	float t0 = (-b + sqrt(b*b-4.0*a*c))/(2.0*a);
	float t1 = (-b - sqrt(b*b-4.0*a*c))/(2.0*a);
	//cout << t0 << " " << t1 << endl;
	if (t0 > ray.t_min && t1 > ray.t_min && t0 < ray.t_max && t1 < ray.t_max)
	{
		Point point = ray.pos + ray.dir*min(t0,t1);
		Vector n = point - center;

		for (int i = 0 ; i < transforms->size(); i++)
		{
			//for each matrix
			for (int j = transforms->at(i).transforms.size()-1; j >= 0; j--)
			//for(int j = 0; j < transforms->at(i).transforms.size(); j++)
			{
				Matrix m = transforms->at(i).transforms.at(j);
				Matrix inverse = transforms->at(i).nTransforms.at(j);

				point = inverse*point;
				if (!m.type.compare("scale")){
					m.transpose();
					n = m*n;
					m.transpose();
					//point = m*point;
				}
				else if(!m.type.compare("rotate")){
					n = inverse*n;
				}
			}
		}
		*local = LocalGeo(point,  Normal(n.x, n.y, n.z));
		*thit = min(t0,t1);
		ray = newr;
		return true;
	}
	else
	{
		ray = newr;
		return false;
	}
	/*Vector L = ray.pos - center;
	Vector r = ray.dir;
	r.normalize();
	float a = r.dot(r);
	float b = 2 * r.dot(L);
	float c = L.dot(L) - (radius*radius);

	//quadratic equation
	float t0, t1;
	float discr = b * b - 4 * a * c;
	if(discr < 0){
		ray = newr;
		return false;
	}
	else if(discr == 0){
		t0 = t1 = -0.5 * b / a;
	} else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		t0 = q / a;
		t1 = c / q;
	}

	//get closer intersection to camera
	if(t0 < t1){
		if(t0 < ray.t_min || t0 > ray.t_max){
			ray = newr;
			return false;
		} else{
			*thit = t0;
			Point intersect = ray.pos + (r*t0);
			//calculate normal
			Vector normv = intersect-center;
			Normal normal = Normal(normv.x, normv.y, normv.z);
			*local = LocalGeo(intersect, normal);
		}
	}else{
		if(t1 < ray.t_min || t1 > ray.t_max){
			ray = newr;
			return false;
		}else{
			*thit = t1;
			Point intersect = ray.pos + (r*t1);
			//calculate normal
			Vector normv = intersect-center;
			Normal normal = Normal(normv.x, normv.y, normv.z);
			*local = LocalGeo(intersect, normal);
		}
	}*/


	//ray = newr;
	return true;
	//bool returnVal = Sphere::intersect(ray, thit, local);
	//if(returnVal == true)
		//cout << "Intersect!!" << endl;
}

bool TransSphere::intersectP(Ray& ray){
	float dummyt;
	LocalGeo dummyGeo;
	return intersect(ray, &dummyt, &dummyGeo);
}

bool TransSphere::isTransformed()
{
	return true;
}

vector<Transform> TransSphere::getTrans()
{
	return *transforms;
}
