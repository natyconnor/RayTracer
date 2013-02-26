#ifndef SAMPLER
#define SAMPLER
#include "Sample.cpp"


class Sampler
{
	int width, height;
	float currentX, currentY;
public:
	Sampler() { width=0; height=0; };
	Sampler(int x, int y);
	bool getSample(Sample* sample);

};

inline Sampler::Sampler(int x, int y)
{
	width = x;
	height = y;
	currentX = 0.5; //make center of pixel
	currentY = 0.5;
}

inline bool Sampler::getSample(Sample* sample){
	if(currentY > height && currentX > width){
		return false;
	}
	if(currentX > width){
		currentX = 0.5;
		currentY += 1;
	}
	*sample = Sample(currentX, currentY);
	currentX += 1;
	return true;
}

#endif