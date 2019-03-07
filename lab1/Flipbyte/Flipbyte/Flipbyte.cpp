#include "pch.h"
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

const string INVALID_ARGUMENTS_COUNT = "Invalid arguments count\nUsage: flipbyte.exe <input byte>\n";
const string WRONG_NUMBER = "The second argument must be a number greater than 0 and less than 255\n";

unsigned int GetFlipByte(unsigned int inputByte)
{
	vector<int> arrayOfPositions;
	bitset<8> bitSequence(inputByte);
	size_t bitSequenceLength = bitSequence.size() - 1;

	for (unsigned int i = 0; i < bitSequence.size(); i++)
	{
		if (bitSequence.test(i))
		{
			bitSequence.flip(i) == 0;
			arrayOfPositions.push_back(i);
		}
	}

	for (unsigned int j = 0; j < arrayOfPositions.size(); j++)
	{
		bitSequence[bitSequenceLength - arrayOfPositions[j]] = 1;
	}

	return bitSequence.to_ulong();
}

bool IsCorrectInput(string& inputString, int& inputByte)
{
	try
	{
		inputByte = stoi(inputString);
	}
	catch (const invalid_argument& err)
	{
		return false;
	} 

	if (inputByte < 0 || inputByte > 255)
	{
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	int parametersNumber = argc;
	if (parametersNumber != 2)
	{
		cout << INVALID_ARGUMENTS_COUNT;
		return 1;
	}

	string inputString = argv[1];
	int inputByte;

	if (!IsCorrectInput(inputString, inputByte))
	{
		cout << WRONG_NUMBER;
		return 1;
	}

	cout << GetFlipByte(inputByte) << "\n";

	return 0;
}