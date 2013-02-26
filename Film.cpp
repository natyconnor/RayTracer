#ifndef FILM
#define FILM

#include "Sample.cpp"
#include "Color.cpp"

#include <iostream>

using namespace std;

#include "FreeImage.h"


class Film
{
public:
	Film();
	Film(int width, int height, int bpp);
	void commit(Sample& sample, Color& color);
	void writeImage();

private:
	FIBITMAP* bitmap;
	RGBQUAD myColor;
};

inline Film::Film(){
	FreeImage_Initialise();
	bitmap = FreeImage_Allocate(0, 0, 0);
}

inline Film::Film(int width, int height, int bpp){
	FreeImage_Initialise();
	bitmap = FreeImage_Allocate(width, height, bpp);
}

inline void Film::commit(Sample& sample, Color& color){
	myColor.rgbRed = (color.r * 255.0);
	myColor.rgbGreen = (color.g * 255.0);
	myColor.rgbBlue = (color.b * 255.0);
	FreeImage_SetPixelColor(bitmap, (unsigned int)sample.x, (unsigned int)sample.y, &myColor);
}

inline void Film::writeImage(){
	
	if(FreeImage_Save(FIF_PNG, bitmap, "raytrace.png", 0))
		cout << "Image Saved Successfully!!" << endl;
	
}

#endif