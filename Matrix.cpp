#include "Matrix.h"

#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>



using namespace std;

Matrix::Matrix(void)
{
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			mat[i][j] = 0;
		}
	}
}

Matrix::Matrix(char type, float x, float y, float z){
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat[j][i] = 0;
		}
	}
	if(type == 't')
	{
		this->type = type;
		mat[0][3] = x;
		mat[1][3] = y;
		mat[2][3] = z;

		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
	} else if(type == 's'){
		this->type = type;
		mat[0][0] = x;
		mat[1][1] = y;
		mat[2][2] = z;
		mat[3][3] = 1;
	} else {
		cout << "Wrong type!!!!!!!!!!" << endl;
	}

}
Matrix::Matrix(float x, float y, float z, float angle){
	this->type = 'r';

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
		mat[1][2] = -sin(angle*M_PI/180);
		mat[2][1] = sin(angle*M_PI/180);
		mat[2][2] = cos(angle*M_PI/180);
		mat[3][3] = 1;
	}
	else if (y == 1)
	{
		mat[0][0] = cos(angle*M_PI/180);
		mat[0][2] = sin(angle*M_PI/180);
		mat[1][1] = 1;
		mat[2][0] = -sin(angle*M_PI/180);
		mat[2][2] = cos(angle*M_PI/180);
		mat[3][3] = 1;
	}
	else if (z == 1)
	{
		mat[0][0] = cos(angle*M_PI/180);
		mat[0][1] = -sin(angle*M_PI/180);
		mat[1][0] = sin(angle*M_PI/180);
		mat[1][1] = cos(angle*M_PI/180);
		mat[2][2] = 1;
		mat[3][3] = 1;
	}
}

Matrix::~Matrix(void)
{
}

void Matrix::makeInverse()
{
	if(type == 't'){
		mat[0][3] = -mat[0][3];
		mat[1][3] = -mat[1][3];
		mat[2][3] = -mat[2][3];
	} else if(type == 's') {
		mat[0][0] = 1/mat[0][0];
		mat[1][1] = 1/mat[1][1];
		mat[2][2] = 1/mat[2][2];
	} else {
		makeTranspose();
	}
}


Point Matrix::operator*(Point other){
	float x, y, z;
	x = mat[0][0] * other.x + mat[0][1] * other.y + mat[0][2] * other.z + mat[0][3];
	y = mat[1][0] * other.x + mat[1][1] * other.y + mat[1][2] * other.z + mat[1][3];
	z = mat[2][0] * other.x + mat[2][1] * other.y + mat[2][2] * other.z + mat[2][3];
	return Point(x, y, z);
}

Vector Matrix::operator*(Vector other){
	float x, y, z;
	x = mat[0][0] * other.x + mat[0][1] * other.y + mat[0][2] * other.z + mat[0][3];
	y = mat[1][0] * other.x + mat[1][1] * other.y + mat[1][2] * other.z + mat[1][3];
	z = mat[2][0] * other.x + mat[2][1] * other.y + mat[2][2] * other.z + mat[2][3];
	return Vector(x, y, z);
}

Normal Matrix::operator*(Normal other){
	float x, y, z;
	x = mat[0][0] * other.x + mat[0][1] * other.y + mat[0][2] * other.z + mat[0][3];
	y = mat[1][0] * other.x + mat[1][1] * other.y + mat[1][2] * other.z + mat[1][3];
	z = mat[2][0] * other.x + mat[2][1] * other.y + mat[2][2] * other.z + mat[2][3];
	return Normal(x, y, z);
}

Matrix Matrix::operator*(Matrix &m) {
  Matrix newMat;
  newMat.mat[0][0] += mat[0][0] * m.mat[0][0] + mat[0][1] * m.mat[1][0] + mat[0][2] * m.mat[2][0] + mat[0][3] * m.mat[3][0];
  newMat.mat[0][1] += mat[0][0] * m.mat[0][1] + mat[0][1] * m.mat[1][1] + mat[0][2] * m.mat[2][1] + mat[0][3] * m.mat[3][1];
  newMat.mat[0][2] += mat[0][0] * m.mat[0][2] + mat[0][1] * m.mat[1][2] + mat[0][2] * m.mat[2][2] + mat[0][3] * m.mat[3][2];
  newMat.mat[0][3] += mat[0][0] * m.mat[0][3] + mat[0][1] * m.mat[1][3] + mat[0][2] * m.mat[2][3] + mat[0][3] * m.mat[3][3];

  newMat.mat[1][0] += mat[1][0] * m.mat[0][0] + mat[1][1] * m.mat[1][0] + mat[1][2] * m.mat[2][0] + mat[1][3] * m.mat[3][0];
  newMat.mat[1][1] += mat[1][0] * m.mat[0][1] + mat[1][1] * m.mat[1][1] + mat[1][2] * m.mat[2][1] + mat[1][3] * m.mat[3][1];
  newMat.mat[1][2] += mat[1][0] * m.mat[0][2] + mat[1][1] * m.mat[1][2] + mat[1][2] * m.mat[2][2] + mat[1][3] * m.mat[3][2];
  newMat.mat[1][3] += mat[1][0] * m.mat[0][3] + mat[1][1] * m.mat[1][3] + mat[1][2] * m.mat[2][3] + mat[1][3] * m.mat[3][3];

  newMat.mat[2][0] += mat[2][0] * m.mat[0][0] + mat[2][1] * m.mat[1][0] + mat[2][2] * m.mat[2][0] + mat[2][3] * m.mat[3][0];
  newMat.mat[2][1] += mat[2][0] * m.mat[0][1] + mat[2][1] * m.mat[1][1] + mat[2][2] * m.mat[2][1] + mat[2][3] * m.mat[3][1];
  newMat.mat[2][2] += mat[2][0] * m.mat[0][2] + mat[2][1] * m.mat[1][2] + mat[2][2] * m.mat[2][2] + mat[2][3] * m.mat[3][2];
  newMat.mat[2][3] += mat[2][0] * m.mat[0][3] + mat[2][1] * m.mat[1][3] + mat[2][2] * m.mat[2][3] + mat[2][3] * m.mat[3][3];

  newMat.mat[3][0] += mat[3][0] * m.mat[0][0] + mat[3][1] * m.mat[1][0] + mat[3][2] * m.mat[2][0] + mat[3][3] * m.mat[3][0];
  newMat.mat[3][1] += mat[3][0] * m.mat[0][1] + mat[3][1] * m.mat[1][1] + mat[3][2] * m.mat[2][1] + mat[3][3] * m.mat[3][1];
  newMat.mat[3][2] += mat[3][0] * m.mat[0][2] + mat[3][1] * m.mat[1][2] + mat[3][2] * m.mat[2][2] + mat[3][3] * m.mat[3][2];
  newMat.mat[3][3] += mat[3][0] * m.mat[0][3] + mat[3][1] * m.mat[1][3] + mat[3][2] * m.mat[2][3] + mat[3][3] * m.mat[3][3];
  return newMat;
}

void Matrix::makeIdentity()
{
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(i == j)
				mat[i][j] = 1;
			else
				mat[i][j] = 0;
		}
	}
}

void Matrix::makeTranspose()
{
	float temp;
	for(int i = 0; i < 4; i++){
		for(int j = i; j < 4; j++){
			temp = mat[i][j];
			mat[i][j] = mat[j][i];
			mat[j][i] = temp;
		}
	}
}

void Matrix::print()
{
	for (int i = 0; i < 4; i++)
	{
		cout << "[";
		for (int j = 0; j < 4; j++)
		{
			cout << mat[i][j] << "\t";
		}
		cout << "] " << endl;
	}
	cout << endl;
}
