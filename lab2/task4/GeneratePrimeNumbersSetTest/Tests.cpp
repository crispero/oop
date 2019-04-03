#include "pch.h"
#include "..\GeneratePrimeNumbersSet\GeneratePrimeNumbersSet.h"

TEST_CASE("PreScreeningNumbers() must return vector with prime numbers")
{
	std::vector<bool> resultOfThree = { false, false, true };
	REQUIRE(PreScreeningNumbers(3) == resultOfThree);

	std::vector<bool> resultOfTen = { false, false, true, true, false, true, false, true, false, false };
	REQUIRE(PreScreeningNumbers(10) == resultOfTen);
}

TEST_CASE("GeneratePrimeNumbers() must return vector with prime numbers")
{
	std::set<int> resultOfThree = { 2 };
	REQUIRE(GeneratePrimeNumbers(3) == resultOfThree);

	std::set<int> resultOfTen = { 2, 3, 5, 7 };
	REQUIRE(GeneratePrimeNumbers(10) == resultOfTen);
}