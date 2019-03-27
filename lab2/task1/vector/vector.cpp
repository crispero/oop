#include "pch.h"
#include "Vector.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

void ReadVector(numbers& vf)
{
	while (!std::cin.eof())
	{
		float number;
		if (std::cin >> number)
		{
			vf.push_back(number);
		}
		else
		{
			break;
		}
	}
}	

void ProcessVector(numbers& vf)
{
	std::vector<float>::iterator result = std::min_element(vf.begin(), vf.end());
	float minElement = *result;
	for (int i = 0; i < vf.size(); i++)
	{
		vf[i] *= minElement;
	}
}

void PrintVector(numbers& vf)
{
	for (int i = 0; i < vf.size(); i++)
	{
		std::cout << vf[i] << " ";
	}
}

int main()
{
	numbers vf;

	ReadVector(vf);
	sort(vf.begin(), vf.end());
	ProcessVector(vf);
	PrintVector(vf);

	return 0;
}