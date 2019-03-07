#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const string INVALID_ARGUMENTS_COUNT = "Invalid arguments count\nUsage: invert.exe <matrix file1>\n";
const string ERROR_OPEN_FILE = "Unable to open file for reading\n";
const string ERROR_ZERO_DETERMINANT = "Determinant is zero. No solution\n";

const int MATRIX_X3_SIZE = 3;
const int MATRIX_X2_SIZE = 2;

typedef float MatrixX3[MATRIX_X3_SIZE][MATRIX_X3_SIZE];
typedef float MatrixX2[MATRIX_X2_SIZE][MATRIX_X2_SIZE];

void InitMatrix(ifstream& fin, MatrixX3& mainMatrix)
{
	if (!fin.eof())
	{
		for (int row = 0; row < MATRIX_X3_SIZE; row++)
		{
			for (int col = 0; col < MATRIX_X3_SIZE; col++)
			{
				fin >> mainMatrix[row][col];
			}
		}
	}
}

float DeterminantOfMatrixX3(MatrixX3& mainMatrix)
{
	float det = mainMatrix[0][0] * mainMatrix[1][1] * mainMatrix[2][2]
		+ mainMatrix[0][2] * mainMatrix[1][0] * mainMatrix[2][1]
		+ mainMatrix[0][1] * mainMatrix[1][2] * mainMatrix[2][0]
		- mainMatrix[0][2] * mainMatrix[1][1] * mainMatrix[2][0]
		- mainMatrix[0][0] * mainMatrix[1][2] * mainMatrix[2][1]
		- mainMatrix[0][1] * mainMatrix[1][0] * mainMatrix[2][2];
	return det;
}

bool CheckMatrix(ifstream &fin, MatrixX3 &mainMatrix)
{
	if (!fin.is_open())
	{
		cout << ERROR_OPEN_FILE;
		return false;
	}

	InitMatrix(fin, mainMatrix);

	return true;
}

bool CheckDeterminant(float detOfMatrixX3)
{
	if (detOfMatrixX3 == 0)
	{
		cout << ERROR_ZERO_DETERMINANT;
		return false;
	}

	return true;
}


void CloneMatrix(MatrixX3& mainMatrix, MatrixX3& additionalMatrix)
{
	for (int row = 0; row < MATRIX_X3_SIZE; row++)
	{
 		for (int col = 0; col < MATRIX_X3_SIZE; col++)
		{
			additionalMatrix[row][col] = mainMatrix[row][col];
		}
	}
}

float DeterminantOfMatrixX2(MatrixX3& additionalMatrix, int numRow, int numCol)
{
	MatrixX2 additionalMatrixX2;
	int ki = 0;
	for (int i = 0; i < MATRIX_X3_SIZE; i++)
	{
		if (i != numRow)
		{
			for (int j = 0, kj = 0; j < MATRIX_X3_SIZE; j++)
			{
				if (j != numCol)
				{
					additionalMatrixX2[ki][kj] = additionalMatrix[j][i];
					kj++;
				}
			}
			ki++;
		}	
	}

	float det = additionalMatrixX2[0][0] * additionalMatrixX2[1][1] - additionalMatrixX2[1][0] * additionalMatrixX2[0][1];
	return det;
}

void InverseMatrix(MatrixX3& mainMatrix, MatrixX3& additionalMatrix, MatrixX3& inverseMatrix, float detOfMatrixX3)
{
	int k = 1;
	for (int row = 0; row < MATRIX_X3_SIZE; row++)
	{
		for (int col = 0; col < MATRIX_X3_SIZE; col++)
		{
			mainMatrix[row][col] = DeterminantOfMatrixX2(additionalMatrix, row, col);
			inverseMatrix[row][col] = k * mainMatrix[row][col] / detOfMatrixX3;
			k = -k;
		}
	}
}

void PrintInverseMatrix(MatrixX3& inverseMatrix)
{
	for (int row = 0; row < MATRIX_X3_SIZE; ++row)
	{
		for (int col = 0; col < MATRIX_X3_SIZE; ++col)
		{
			cout << fixed  << setprecision(3) << inverseMatrix[row][col] << " ";
		}
		cout << endl;
	}
}

int main(int argc, char* argv[])
{
	int parametersNumber = argc;

	 if (parametersNumber != 2)
	{
		cout << INVALID_ARGUMENTS_COUNT;
		return 1;
	} 

	string fileName = argv[1];
	ifstream fin(fileName);

	MatrixX3 mainMatrix, additionalMatrix, inverseMatrix;

	if (CheckMatrix(fin, mainMatrix))
	{
		float det = DeterminantOfMatrixX3(mainMatrix);
		if (CheckDeterminant(det))
		{
			CloneMatrix(mainMatrix, additionalMatrix);
			InverseMatrix(mainMatrix, additionalMatrix, inverseMatrix, det);
			PrintInverseMatrix(inverseMatrix);
		}
	}

	return 0;
}