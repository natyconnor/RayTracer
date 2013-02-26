#ifndef COLOR
#define COLOR
class Color
{
public:
	Color() { r=0; g=0; b=0; };
	Color(float red, float green, float blue);
	Color operator + (Color);

	float r, g, b;
};

inline Color::Color(float red, float green, float blue)
{
	r = red;
	g = green;
	b = blue;
}

inline Color Color::operator+ (Color other) {
	Color newColor;
	newColor.r = r + other.r; 
	newColor.g = g + other.g;
	newColor.b = b + other.b;
	return newColor;
}

#endif