#include "Matrix.h"


Matrix::Matrix(void)
{
	//Default matrix is all zeros
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			mat[i][j] = 0;
		}
	}
}

Matrix::Matrix(char type, float x, float y, float z){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			mat[i][j] = 0;
		}
	}
	// scale matrix
	if(type == 's'){
		mat[0][0] = x;
		mat[1][1] = y;
		mat[2][2] = z;
	// translation matrix
	} else if(type == 't'){
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
		mat[3][0] = x;
		mat[3][1] = y;
		mat[3][2] = z;
	}// Need to set up rotation matrices
}

Matrix::~Matrix(void)
{
}
