#include "pch.h"
#include "GeneratePrimeNumbersSet.h"

std::vector<bool> PreScreeningNumbers(int upperBound)
{
	std::vector<bool> primeNumbersVec(upperBound, true);

	primeNumbersVec[0] = primeNumbersVec[1] = false;
	for (unsigned int i = 2; i * i < upperBound; i++)
	{
		if (primeNumbersVec[i])
		{
			for (unsigned int k = i * i; k < upperBound; k += i)
			{
				primeNumbersVec[k] = false;
			}
		}
	}

	return primeNumbersVec;
}

std::set<int> GeneratePrimeNumbers(int upperBound)
{
	std::set<int> primeNumbersSet;
	std::vector<bool> primeNumbersVec = PreScreeningNumbers(upperBound);

	for (unsigned int i = 0; i < primeNumbersVec.size(); i++)
	{
		if (primeNumbersVec[i] == true)
		{
			primeNumbersSet.insert(i);
		}
	}

	return primeNumbersSet;
}
