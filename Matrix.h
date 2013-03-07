#pragma once
class Matrix
{
public:
	float mat[4][4];
	Matrix(void);
	Matrix(char type, float x, float y, float z);
	~Matrix(void);

};

