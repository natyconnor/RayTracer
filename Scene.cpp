#include "Sample.cpp"
#include "Color.cpp"
#include "Film.cpp"
#include "Sampler.cpp"
#include "Point.cpp"
#include "Ray.h"
#include "Camera.h"
#include "RayTracer.h"
#include "Transform.h"
#include "TransSphere.h"
#include "TransTriangle.h"

#include "FreeImage.h"

#define WIDTH 100
#define HEIGHT 100
#define BPP 24
#define _USE_MATH_DEFINES

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>

#include <time.h>
#include <math.h>

using namespace std;

class Scene {
	Point myEyePos;
	//Point myLL, myUL, myUR, myLR;
	int myHeight, myWidth;
	Sampler sampler;
	Sample sample;
	Color color;
	Film film;

	Ray ray;
	Camera camera;
	RayTracer raytracer;

	vector<Point> vertices;
	vector<Primitive*> prims;
	vector<Transform> transforms;

  public:
	Scene();
	//Scene(Point eyePos, Point LL, Point UL, Point UR, Point LR, int height, int width);
	void render();
	void loadScene(std::string file);
};

inline Scene::Scene(){
	transforms = vector<Transform>();
}

/*inline Scene::Scene(Point eyePos, Point LL, Point UL, Point UR, Point LR, int height, int width)
{
	myEyePos = eyePos;
	myLL = LL;
	myUL = UL;
	myUR = UR;
	myUL = UL;
	myHeight = height;
	myWidth = width;
	sampler = Sampler(width, height);
	sample = Sample();
	color = Color();
	film = Film(width, height, 24);

	ray = Ray();
	camera = Camera(eyePos, myLL, myUL, myUR, myLR, myHeight, myWidth);
	raytracer = RayTracer(3, myEyePos);
}*/

inline void Scene::render(){
	while(sampler.getSample(&sample)){
		color = Color();
		camera.generateRay(sample, &ray);
		raytracer.trace(ray, 0, &color);
		film.commit(sample, color);
	}
	film.writeImage();
}

int main(int argc, char *argv[]){
	cout << argv[1] << endl;
	Scene s;
	s.loadScene(string(argv[1]));
	//Scene s = Scene(Point(0,0,0), Point(-1,-1, -3), Point(-1, 1, -3), Point(1, 1, -3), Point(1,-1, -3), 500, 1000);
	s.render();
	return 0;
}

void Scene::loadScene(std::string file) {
  //store variables and set stuff at the end
  int width, height;
  int maxdepth = 1;

  Color currentKA = Color(0.2, 0.2, 0.2);
  Color currentKD = Color();
  Color currentKS = Color();
  Color currentKR = Color();
  float currentSP = 20.0f;


  std::string fname = "output.bmp";
  std::ifstream inpfile(file.c_str());
  if(!inpfile.is_open()) {
    std::cout << "Unable to open file" << std::endl;
  } else {
    std::string line;
    //MatrixStack mst;
    while(inpfile.good()) {
      std::vector<std::string> splitline;
      std::string buf;
      std::getline(inpfile,line);
      std::stringstream ss(line);
      while (ss >> buf) {
        splitline.push_back(buf);
      }
      //Ignore blank lines
      if(splitline.size() == 0) {
        continue;
      }
      //Ignore comments
      if(splitline[0][0] == '#') {
        continue;
      }
      //Valid commands:
      //size width height
      //  must be first command of file, controls image size
      else if(!splitline[0].compare("size")) {
        width = atoi(splitline[1].c_str());
        height = atoi(splitline[2].c_str());
      }
      //maxdepth depth
      //  max # of bounces for ray (default 5)
      else if(!splitline[0].compare("maxdepth")) {
         maxdepth = atoi(splitline[1].c_str());
      }
      //output filename
      //  output file to write image to 
      else if(!splitline[0].compare("output")) {
        fname = splitline[1];
      }
      //camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov
      //  speciﬁes the camera in the standard way, as in homework 2.
      else if(!splitline[0].compare("camera")) {
        // lookfrom:
        Point lookfrom = Point(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));

        Point lookat = Point(atof(splitline[4].c_str()), atof(splitline[5].c_str()), atof(splitline[6].c_str()));
        Vector up = Vector(atof(splitline[7].c_str()), atof(splitline[8].c_str()), atof(splitline[9].c_str()));
		//up.normalize();

        float fov = atof(splitline[10].c_str());
		
		/*float r = width/height;

		float imgPlaneHeight = 2 * tan(fov/2*M_PI/180/2);
		float fovh = 2 * atan(imgPlaneHeight * r /2);
		float imgPlaneWidth = 2 * tan(fovh/2);

		 Trying to find 4 corners
		Vector dir = lookat - lookfrom; //also normal to image plane
		dir.normalize();
		Point center = lookfrom + dir;
		Point top = center + up * imgPlaneHeight/2;
		Vector leftdir = up.cross(dir);
		leftdir.normalize();
		Point left = center + leftdir * imgPlaneWidth/2;
		Point right = center + (leftdir * -1) * imgPlaneWidth/2;

		Point LL = left + (up*-1) * imgPlaneHeight/2;
		Point UL = top + leftdir * imgPlaneWidth/2;
		Point UR = top + (leftdir*-1) * imgPlaneWidth/2;
		Point LR = right + (up*-1) * imgPlaneHeight/2;

		myEyePos = lookfrom;
		myLL = LL;
		myUL = UL;
		myUR = UR;
		myLR = LR;
		myHeight = height;
		myWidth = width;*/

		sampler = Sampler(width, height);
		sample = Sample();
		color = Color();
		film = Film(width, height, 24);

		ray = Ray();
		//camera = Camera(myEyePos, myLL, myUL, myUR, myLR, myHeight, myWidth);
		camera = Camera(lookfrom, lookat, up, fov, width, height);
		raytracer = RayTracer(maxdepth, lookfrom);
	  
	  }
      //sphere x y z radius
      //  Deﬁnes a sphere with a given position and radius.
      else if(!splitline[0].compare("sphere")) {
		Point center = Point(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
		float r = atof(splitline[4].c_str());
		if(transforms.size() == 0){
			Sphere* s = new Sphere(center,r,BRDF(currentKD, currentKS, currentKA, currentKR, currentSP));
			raytracer.addPrim(s);
		} else {
			TransSphere* s = new TransSphere(center,r,BRDF(currentKD, currentKS, currentKA, currentKR, currentSP), new vector<Transform>(transforms));
			raytracer.addPrim(s);
		}
      }
      //maxverts number
      //  Deﬁnes a maximum number of vertices for later triangle speciﬁcations. 
      //  It must be set before vertices are deﬁned.
      else if(!splitline[0].compare("maxverts")) {
        // Care if you want
        // Here, either declare array size
        // Or you can just use a STL vector, in which case you can ignore this
      }
      //maxvertnorms number
      //  Deﬁnes a maximum number of vertices with normals for later speciﬁcations.
      //  It must be set before vertices with normals are deﬁned.
      else if(!splitline[0].compare("maxvertnorms")) {
        // Care if you want
      }
      //vertex x y z
      //  Deﬁnes a vertex at the given location.
      //  The vertex is put into a pile, starting to be numbered at 0.
      else if(!splitline[0].compare("vertex")) {
        Point v = Point(atof(splitline[1].c_str()),atof(splitline[2].c_str()), atof(splitline[3].c_str()));
        // Create a new vertex with these 3 values, store in some array

		vertices.push_back(v);
      }
      //vertexnormal x y z nx ny nz
      //  Similar to the above, but deﬁne a surface normal with each vertex.
      //  The vertex and vertexnormal set of vertices are completely independent
      //  (as are maxverts and maxvertnorms).
      else if(!splitline[0].compare("vertexnormal")) {
        // x: atof(splitline[1].c_str()),
        // y: atof(splitline[2].c_str()),
        // z: atof(splitline[3].c_str()));
        // nx: atof(splitline[4].c_str()),
        // ny: atof(splitline[5].c_str()),
        // nz: atof(splitline[6].c_str()));
        // Create a new vertex+normal with these 6 values, store in some array
      }
      //tri v1 v2 v3
      //  Create a triangle out of the vertices involved (which have previously been speciﬁed with
      //  the vertex command). The vertices are assumed to be speciﬁed in counter-clockwise order. Your code
      //  should internally compute a face normal for this triangle.
      else if(!splitline[0].compare("tri")) {
        float v1 = atof(splitline[1].c_str());
        float v2 = atof(splitline[2].c_str());
        float v3 = atof(splitline[3].c_str());

		if(transforms.size() == 0){
			Triangle* t = new Triangle(vertices.at(v1),vertices.at(v2),vertices.at(v3), BRDF(currentKD, currentKS, currentKA, currentKR, currentSP));
			raytracer.addPrim(t);
		} else {
			TransTriangle* t = new TransTriangle(vertices.at(v1),vertices.at(v2),vertices.at(v3), BRDF(currentKD, currentKS, currentKA, currentKR, currentSP), new vector<Transform>(transforms));
			raytracer.addPrim(t);
		}
      }
      //trinormal v1 v2 v3
      //  Same as above but for vertices speciﬁed with normals.
      //  In this case, each vertex has an associated normal, 
      //  and when doing shading, you should interpolate the normals 
      //  for intermediate points on the triangle.
      else if(!splitline[0].compare("trinormal")) {
        // v1: atof(splitline[1].c_str())
        // v2: atof(splitline[2].c_str())
        // v3: atof(splitline[3].c_str())
        // Create new triangle:
        //   Store pointer to array of vertices (Different array than above)
        //   Store 3 integers to index into array
        //   Store current property values
        //   Store current top of matrix stack
      }
      //translate x y z
      //  A translation 3-vector
      else if(!splitline[0].compare("translate")) {
        float x = atof(splitline[1].c_str());
        float y = atof(splitline[2].c_str());
        float z = atof(splitline[3].c_str());
        // Update top of matrix stack
		transforms.back().addTranslate(-x, -y, -z);
      }
      //rotate x y z angle
      //  Rotate by angle (in degrees) about the given axis as in OpenGL.
      else if(!splitline[0].compare("rotate")) {
        float x = atof(splitline[1].c_str());
        float y = atof(splitline[2].c_str());
        float z = atof(splitline[3].c_str());
		float angle = atof(splitline[4].c_str());
        // Update top of matrix stack
		transforms.back().addRotate(x, y, z, -angle);
      }
      //scale x y z
      //  Scale by the corresponding amount in each axis (a non-uniform scaling).
      else if(!splitline[0].compare("scale")) {
        float x = atof(splitline[1].c_str());
        float y = atof(splitline[2].c_str());
        float z = atof(splitline[3].c_str());
        // Update top of matrix stack
		transforms.back().addScale(1/x, 1/y, 1/z);
      }
      //pushTransform
      //  Push the current modeling transform on the stack as in OpenGL. 
      //  You might want to do pushTransform immediately after setting 
      //   the camera to preserve the “identity” transformation.
      else if(!splitline[0].compare("pushTransform")) {
        transforms.push_back(Transform());
      }
      //popTransform
      //  Pop the current transform from the stack as in OpenGL. 
      //  The sequence of popTransform and pushTransform can be used if 
      //  desired before every primitive to reset the transformation 
      //  (assuming the initial camera transformation is on the stack as 
      //  discussed above).
      else if(!splitline[0].compare("popTransform")) {
        transforms.pop_back();
      }
      //directional x y z r g b
      //  The direction to the light source, and the color, as in OpenGL.
      else if(!splitline[0].compare("directional")) {
        Vector dir = Vector(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
        Color i = Color(atof(splitline[4].c_str()), atof(splitline[5].c_str()), atof(splitline[6].c_str()));
        // add light to scene...
		DirectionalLight* dl = new DirectionalLight(dir,i);
		raytracer.addLight(dl);
      }
      //point x y z r g b
      //  The location of a point source and the color, as in OpenGL.
      else if(!splitline[0].compare("point")) {
        Point p = Point(atof(splitline[1].c_str()), atof(splitline[2].c_str()), atof(splitline[3].c_str()));
        Color i = Color(atof(splitline[4].c_str()), atof(splitline[5].c_str()), atof(splitline[6].c_str()));
        // add light to scene...
		PointLight* pl = new PointLight(p,i);
		raytracer.addLight(pl);
      }
      //attenuation const linear quadratic
      //  Sets the constant, linear and quadratic attenuations 
      //  (default 1,0,0) as in OpenGL.
      else if(!splitline[0].compare("attenuation")) {
        // const: atof(splitline[1].c_str())
        // linear: atof(splitline[2].c_str())
        // quadratic: atof(splitline[3].c_str())
      }
      //ambient r g b
      //  The global ambient color to be added for each object 
      //  (default is .2,.2,.2)
      else if(!splitline[0].compare("ambient")) {
        float r = atof(splitline[1].c_str());
        float g = atof(splitline[2].c_str());
        float b = atof(splitline[3].c_str());

		currentKA = Color(r,g,b);
      }
      //diﬀuse r g b
      //  speciﬁes the diﬀuse color of the surface.
      else if(!splitline[0].compare("diffuse")) {
        float r = atof(splitline[1].c_str());
        float g = atof(splitline[2].c_str());
        float b = atof(splitline[3].c_str());
        // Update current properties
		currentKD = Color(r,g,b);
      }
      //specular r g b 
      //  speciﬁes the specular color of the surface.
      else if(!splitline[0].compare("specular")) {
        float r = atof(splitline[1].c_str());
        float g = atof(splitline[2].c_str());
        float b = atof(splitline[3].c_str());
        // Update current properties
		currentKS = Color(r,g,b);
		//currentKR = Color(r,g,b);
      }
      //shininess s
      //  speciﬁes the shininess of the surface.
      else if(!splitline[0].compare("shininess")) {
        currentSP = atof(splitline[1].c_str());
      }

	  //reflection r g b
	  // specifies the reflection color of the surface
	  else if(!splitline[0].compare("reflection")) {
		  float r = atof(splitline[1].c_str());
		  float g = atof(splitline[2].c_str());
		  float b = atof(splitline[3].c_str());
		  // Update current properties
		  currentKR = Color(r,g,b);
	  }
      //emission r g b
      //  gives the emissive color of the surface.
      else if(!splitline[0].compare("emission")) {
        // r: atof(splitline[1].c_str())
        // g: atof(splitline[2].c_str())
        // b: atof(splitline[3].c_str())
        // Update current properties
      } else {
        std::cerr << "Unknown command: " << splitline[0] << std::endl;
      }
    }
    inpfile.close();
  }
}


