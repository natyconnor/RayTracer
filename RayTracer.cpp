#include "RayTracer.h"
#include "Point.cpp"

RayTracer::RayTracer(void)
{
	threshold = 10;
	//prims.push_back(Sphere());
	eyePos = Point(0, 0, 0);
}

RayTracer::RayTracer(int thresh, Point eye){
	threshold = thresh;

	//Sphere* sph1 = new Sphere(Point(0,0,-20), 3.0, BRDF(Color(1,0,1), Color(1,1,1), Color(0.1,0.1,0.1), Color(), 50));
	//Sphere* sph2 = new Sphere(Point(-2,2,-15), 1.0, BRDF(Color(1,1,0), Color(1,1,1), Color(0.1,0.1,0.1), Color(), 50));
	//Sphere* sph3 = new Sphere(Point(-2,-2,-15), 1.0, BRDF(Color(0,1,1), Color(1,1,1), Color(0.1,0.1,0.1), Color(), 50));
	//Triangle* tri = new Triangle(Point(5,5,-17), Point(1,4,-20), Point(6,-1,-20), BRDF(Color(0.1,0.1,0.1), Color(), Color(0.1,0.1,0.1), Color(1,1,1), 50));
	
	//prims.push_back(tri);
	//prims.push_back(sph1);
	//prims.push_back(sph2);
	//prims.push_back(sph3);

	//DirectionalLight* dl1 = new DirectionalLight(Vector(0.57735027, -0.57735027, -0.57735027), Color(1,1,1));
	//DirectionalLight* dl2 = new DirectionalLight(Vector(0.57735027, 0.57735027, -0.57735027), Color(0,0,1));
	//lights.push_back(dl1);
	//lights.push_back(dl2);
	eyePos = eye;
}


RayTracer::~RayTracer(void)
{
}


void RayTracer::trace(Ray& ray, int depth, Color* color){
	if(depth > threshold){
		return;
	}

	float thit;
	LocalGeo intersection;
	LocalGeo closestInter;
	float minDistance = 99999;
	Primitive* closest = 0;

	//transorms
	bool transformed = false;
	vector<Transform> transforms;

	//loop through all primitives
	for(vector<Primitive*>::iterator iter = prims.begin(); iter != prims.end(); ++iter){
		Primitive* s = *iter;
		//if intersection
		if((*s).intersect(ray, &thit, &intersection)){
			//keep track of the closest intersection to the camera, since that is what we will draw
			//float dist = (intersection.pos - eyePos).magnitude();
			if(thit < minDistance){
				minDistance = thit;
				closest = s;
				closestInter = intersection;

				//get transforms of new closest object
				if((*s).isTransformed() == true) {
					transformed = true;
					transforms = (*s).getTrans();
				} else {
					transformed = false;
				}
			}
		}
	}
	//compute shading
	if(minDistance != 99999){

		if(transformed == true){
			for (int i = 0 ; i < transforms.size(); i++)
			{
				//for each matrix
				for (int j = 0; j < transforms.at(i).transforms.size(); j++)
				{
					Matrix m = transforms.at(i).transforms.at(j);
					Matrix n = transforms.at(i).nTransforms.at(j);
					if (m.mat[0][0] == 1 && m.mat[1][1] == 1 && m.mat[2][2] == 1) //translate
					{
						ray.pos = m*ray.pos;

						//closestInter.pos = n*(closestInter.pos);

						//ray.dir = m*ray.dir;
						//m.transpose();
						//closestInter.norm = n*(closestInter.norm);
						//m.transpose();
					}
					else //scale
					{
						ray.pos = m*ray.pos;
						ray.dir = m*ray.dir;

						//closestInter.pos = n*(closestInter.pos);

						//m.transpose();
						//closestInter.norm = n*(closestInter.norm);
						//intersection.norm.normalize();
						//m.transpose();

					}
				}
			}
		}

		Ray lray = Ray();
		Ray tlray = Ray();
		Color lcolor = Color();
		BRDF brdf = BRDF();
		(*closest).getBRDF(closestInter, &brdf);
		*color = brdf.ka;

		//Reflection info. Need r vector like in specular. Find way to send this to shading?
		Vector rDir = ray.dir - (closestInter.norm * (2 * closestInter.norm.dot(ray.dir)));
		rDir.normalize();
		Ray r = Ray(closestInter.pos, rDir, 0.005, ray.t_max);
		/////////////////////////////////////////////////////////////////////////////////


		for(vector<Light*>::iterator lIter = lights.begin(); lIter != lights.end(); ++ lIter){
			Light* l = *lIter;
			(*l).generateLightRay(closestInter, &lray, &lcolor);
			//tlray = lray;

			//check for intersection with primitives for shadows
			bool isShadow = false;
			for(vector<Primitive*>::iterator iter = prims.begin(); iter != prims.end(); ++iter){
				Primitive* s = *iter;
				if((*s).intersectP(lray)){
					isShadow = true;
					break;
				}
			}

			if(transformed == true){
				for (int i = 0 ; i < transforms.size(); i++)
				{
					//for each matrix
					for (int j = 0; j < transforms.at(i).transforms.size(); j++)
					{
						Matrix m = transforms.at(i).transforms.at(j);
						Matrix n = transforms.at(i).nTransforms.at(j);
						if (m.mat[0][0] == 1 && m.mat[1][1] == 1 && m.mat[2][2] == 1) //translate
						{
							//lray.pos = m*lray.pos;
							//closestInter.pos = n*(closestInter.pos);

							//ray.dir = m*ray.dir;
							//m.transpose();
							//closestInter.norm = n*(closestInter.norm);
							//m.transpose();
						}
						else //scale
						{
							//lray.pos = m*lray.pos;
							//lray.dir = m*lray.dir;
							//closestInter.pos = n*(closestInter.pos);

							//m.transpose();
							//closestInter.norm = n*(closestInter.norm);
							//intersection.norm.normalize();
							//m.transpose();

						}
					}
				}
			}


			if(!isShadow){
				Color refColor = Color();

				//make recursive call if there is any reflectivity
				if(brdf.kr.r != 0 && brdf.kr.g != 0 && brdf.kr.b != 0)
					trace(r, depth+1, &refColor);
				//calculate Phong stuff
				*color = *color + shading(closestInter, brdf, ray, lray, lcolor) + brdf.kr*refColor;
				//*color = Color(1,0,0);
			}
		}
		


	}
}

Color RayTracer::shading(LocalGeo& point, BRDF brdf, Ray& origRay, Ray& lray, Color lcolor){
	//diffuse component
	//dot product between normal and light vectors
	float diff = point.norm.dot(lray.dir);

	//specular component
	Vector v = origRay.pos - point.pos; //for reflections, eye needs to be point of where first ray came from
	v.normalize();
	Vector r = (lray.dir * -1) + (point.norm * (2 * diff));
	r.normalize();
	float spec = r.dot(v);

	return (lcolor * brdf.kd) * max(diff,0.0f) + (lcolor * brdf.ks) * pow(max(spec,0.0f),brdf.sp);
}

void RayTracer::addPrim(Primitive* prim){
	prims.push_back(prim);
}

void RayTracer::addLight(Light* l){
	lights.push_back(l);
}
