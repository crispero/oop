#include "pch.h"
#include "PrintVector.h"
#include <iostream>
#include <iomanip>

void PrintVector(numbers& vf)
{
	for (int i = 0; i < vf.size(); i++)
	{
		std::cout << std::setprecision(3) << std::fixed << vf[i] << " ";
	}
}