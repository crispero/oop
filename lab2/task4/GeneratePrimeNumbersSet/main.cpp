#include "pch.h"
#include <iostream>
#include "GeneratePrimeNumbersSet.h"

int main()
{
	unsigned int num;
	std::cin >> num;
	std::set<int> primeNumbersSet = GeneratePrimeNumbers(num);
	for (auto it = primeNumbersSet.begin(); it != primeNumbersSet.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	return 0;
}