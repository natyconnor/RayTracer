#define _USE_MATH_DEFINES
#include "Matrix.h"
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

Matrix::Matrix()
{
	//identity matrix
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat[j][i] = 0;
		}
	}
	mat[0][0] = 1;
	mat[1][1] = 1;
	mat[2][2] = 1;
	mat[3][3] = 1;
}

Matrix::Matrix(string transform, float x, float y, float z)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat[j][i] = 0;
		}
	}
	if (!transform.compare("translate"))
	{
		cout << "translating " << x << " " << y  << " " << z << endl;
		mat[3][0] = x;
		mat[3][1] = y;
		mat[3][2] = z;
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
		print();
	}
	else if (!transform.compare("scale"))
	{
		cout << "scaling " << x << " " << y  << " " << z << endl;
		mat[0][0] = x;
		mat[1][1] = y;
		mat[2][2] = z;
		mat[3][3] = 1;
		print();
	}
	else
	{
		cout << "Incorrect transform type in Matrix.cpp" << endl;
	}
}

Matrix::Matrix(float x, float y, float z, float angle)
{
	cout << "rotating " << x << " " << y  << " " << z << " " << angle << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat[j][i] = 0;
		}
	}
	if (x == 1)
	{
		mat[0][0] = 1;
		mat[1][1] = cos(angle*M_PI/180);
		mat[2][1] = -sin(angle*M_PI/180);
		mat[1][2] = sin(angle*M_PI/180);
		mat[2][2] = cos(angle*M_PI/180);
		mat[3][3] = 1;
	}
	else if (y == 1)
	{
		mat[0][0] = cos(angle*M_PI/180);
		mat[3][0] = sin(angle*M_PI/180);
		mat[1][1] = 1;
		mat[0][2] = -sin(angle*M_PI/180);
		mat[2][2] = cos(angle*M_PI/180);
		mat[3][3] = 1;
	}
	else if (z == 1)
	{
		mat[0][0] = cos(angle*M_PI/180);
		mat[1][0] = -sin(angle*M_PI/180);
		mat[0][1] = sin(angle*M_PI/180);
		mat[1][1] = cos(angle*M_PI/180);
		mat[2][2] = 1;
		mat[3][3] = 1;
	}
	print();
}

 Point Matrix::operator*(Point p)
 {
	 //print();
	 //cout << "In: " << p.x << " " << p.y << " " << p.z << endl;
	 float a = mat[0][0]*p.x + mat[1][0]*p.y + mat[2][0]*p.z + mat[3][0]*1;
	 float b = mat[0][1]*p.x + mat[1][1]*p.y + mat[2][1]*p.z + mat[3][1]*1;
	 float c = mat[0][2]*p.x + mat[1][2]*p.y + mat[2][2]*p.z + mat[3][2]*1;
	 //float d = mat[0][3]*vec.x + mat[1][3]*vec.y + mat[2][3]*vec.z + mat[3][3]*1;
	 //cout << "Out: " << a << " " << b << " " << c << endl;
	 return Point(a,b,c);
 }

 Vector Matrix::operator*(Vector vec)
 {
	 //print();
	 //vec.print();
	 //cout << "In: " << vec.x << " " << vec.y << " " << vec.z << endl;
	 float a = mat[0][0]*vec.x + mat[1][0]*vec.y + mat[2][0]*vec.z + mat[3][0]*1;
	 float b = mat[0][1]*vec.x + mat[1][1]*vec.y + mat[2][1]*vec.z + mat[3][1]*1;
	 float c = mat[0][2]*vec.x + mat[1][2]*vec.y + mat[2][2]*vec.z + mat[3][2]*1;
	 //float d = mat[0][3]*vec.x + mat[1][3]*vec.y + mat[2][3]*vec.z + mat[3][3]*1;
	 //cout << "Out: " << a << " " << b << " " << c << endl;
	 return Vector(a,b,c);
 }

 void Matrix::print()
 {
	 for (int i = 0; i < 4; i++)
	 {
		 cout << "[";
		 for (int j = 0; j < 4; j++)
		 {
			 cout << mat[j][i] << " ";
		 }
		 cout << "] " << endl;
	 }
	 cout << endl;
 }

