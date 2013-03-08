#include "TransTriangle.h"

TransTriangle::TransTriangle(Point a, Point b, Point c, BRDF brdf, vector<Transform>* transformations)
{
	v1 = a;
	v2 = b;
	v3 = c;
	myBRDF = brdf;
	transforms = transformations;
	x = 0;
}

void TransTriangle::getBRDF(LocalGeo& local, BRDF* brdf)
{
	*brdf = myBRDF;
}

bool TransTriangle::intersect(Ray& ray, float *thit, LocalGeo* local)
{
	//cout << "new" << endl;
	//ray.dir.print();
	Ray r = Ray(ray.pos, ray.dir, ray.t_min, ray.t_max);
	for (int i = 0 ; i < transforms->size(); i++)
	{
		
		//for each matrix
		for (int j = 0; j < transforms->at(i).transforms.size(); j++)
		{
			Matrix m = transforms->at(i).transforms.at(j);
			if (m.mat[0][0] == 1 && m.mat[1][1] == 1 && m.mat[2][2] == 1) //translate
			{
				//cout << "translate" << endl;
				//m.print();
				ray.pos = m*ray.pos;
				//ray.dir = m*ray.dir;
			}
			else //scale
			{
				//cout << "scale" << endl;
				//m.print();
				ray.pos = m*ray.pos;
				ray.dir = m*ray.dir;
			}
		}
	}
	//////////////////////////////////
	/*Geometric solution*/
	Normal n = normal();

	//check if ray and triangle are parallel
	if(n.dot(ray.dir) == 0){
		ray = r;
		return false;
	}
	//compute D of plane equation
	float d = n.dot(v1);

	//with equation of ray and equation of plane, we can calculate thit
	float t = -(n.dot(ray.pos) + d) / (n.dot(ray.dir));

	//check if triangle is not within ray's length
	if(t < ray.t_min || t > ray.t_max){
		ray = r;
		return false;
	}

	Point p = ray.pos + (ray.dir * t);

	//Now with point intersecting plane, use inside out test
	//to see if it's in the triangle
	Vector c;

	//edge 1
	Vector edge1 = v2 - v1;
	Vector vp1 = p - v1;
	c = edge1.cross(vp1);
	//c = vp1.cross(edge1);
	if(n.dot(c) < 0){
		ray = r;
		return false; //p is on the wrong side of the edge
	}

	//edge 2
	Vector edge2 = v3 - v2;
	Vector vp2 = p - v2;
	c = edge2.cross(vp2);
	//c = vp2.cross(edge2);
	if(n.dot(c) < 0){
		ray = r;
		return false; //p is on the wrong side of the edge
	}

	//edge 3
	Vector edge3 = v1 - v3;
	Vector vp3 = p - v3;
	c = edge3.cross(vp3);
	//c = vp3.cross(edge3);
	if(n.dot(c) < 0){
		ray = r;
		return false; //p is on the wrong side of the edge
	}

	*thit = t;
	

	for (int i = 0 ; i < transforms->size(); i++)
		{
			//for each matrix
			for (int j = transforms->at(i).transforms.size()-1; j >= 0; j--)
			//for(int j = 0; j < transforms->at(i).transforms.size(); j++)
			{
				Matrix m = transforms->at(i).transforms.at(j);
				Matrix inverse = transforms->at(i).nTransforms.at(j);

				p = m * p;
				if (!m.type.compare("scale")){
					m.transpose();
					n = m*n;
					//p = m*p;
					m.transpose();
				}
				else if(!m.type.compare("rotate")){
					n = inverse*n;
				}
			}
		}

	n.normalize();
	*local = LocalGeo(p, n);

	
	//ray.dir.print();
	ray = r;
	//ray.dir.print();
	return true;
	//bool returnVal = Triangle::intersect(ray, thit, local);
	//if(returnVal == true)
	//	cout << "Intersect!!" << endl;
	

}


bool TransTriangle::intersectP(Ray& ray){
	float dummyt;
	LocalGeo dummyGeo;
	return intersect(ray, &dummyt, &dummyGeo);
}
bool TransTriangle::isTransformed()
{
	return true;
}

vector<Transform> TransTriangle::getTrans()
{
	return *transforms;
}


Normal TransTriangle::normal()
{
	Vector vec1 = v2 - v1;
	Vector vec2 = v3 - v1;


	//can't implement a cross product function in Vector class that returns a Normal
	//probably because Vector and Normal will include each other
	//cross product between vec1 and vec2

	return Normal(vec1.y*vec2.z - vec1.z*vec2.y, vec1.z*vec2.x - vec1.x*vec2.z, vec1.x*vec2.y - vec1.y*vec2.x);
}
