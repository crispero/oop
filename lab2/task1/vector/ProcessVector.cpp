#include "pch.h"
#include "ProcessVector.h"

void ProcessVector(numbers& vf)
{
	float minNum = vf[0];
	for (int i = 0; i < vf.size(); i++)
	{
		vf[i] *= minNum;
	}
}