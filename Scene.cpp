#include "Sample.cpp"
#include "Color.cpp"
#include "Film.cpp"
#include "Sampler.cpp"
#include "Point.cpp"
#include "Ray.h"
#include "Camera.h"
#include "RayTracer.h"

#include "FreeImage.h"

#define WIDTH 100
#define HEIGHT 100
#define BPP 24

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#include <time.h>
#include <math.h>

using namespace std;

class Scene {
	Point myEyePos;
	Point myLL, myUL, myUR, myLR;
	int myHeight, myWidth;
	Sampler sampler;
	Sample sample;
	Color color;
	Film film;

	Ray ray;
	Camera camera;
	RayTracer raytracer;

  public:
	Scene(Point eyePos, Point LL, Point UL, Point UR, Point LR, int height, int width);
	void render();
};

inline Scene::Scene(Point eyePos, Point LL, Point UL, Point UR, Point LR, int height, int width)
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
	raytracer = RayTracer(10, myEyePos);
}

inline void Scene::render(){
	while(sampler.getSample(&sample)){
		camera.generateRay(sample, &ray);
		raytracer.trace(ray, 5, &color);
		film.commit(sample, color);
	}
	film.writeImage();
}

int main(int argc, char *argv[]){
	/*FreeImage_Initialise();

	FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BPP);
	RGBQUAD color;

	if(!bitmap)
		exit(1);

	for (int i = 0; i < WIDTH; i++){
		for(int j = 0; j < HEIGHT; j++){
			color.rgbRed = 0;
			color.rgbGreen = (double)i / WIDTH * 255.0;
			color.rgbBlue = (double)j / HEIGHT * 255.0;
			FreeImage_SetPixelColor(bitmap, i, j, &color);
		}
	}

	if(FreeImage_Save(FIF_PNG, bitmap, "test.png", 0))
		cout << "Image_successfully_saved" << endl;*/
		
	cout << "Starting..." << endl;
	Scene s = Scene(Point(0,0,0), Point(-1,-1, -1), Point(-1, 1, -1), Point(1, 1, -1), Point(1,-1, -1), 500, 500);
	s.render();
	return 0;
}

