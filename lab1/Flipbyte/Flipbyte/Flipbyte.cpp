#include "pch.h"
#include <bitset>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
	vector<int> arrayOfPositions;
	int inputByte = atoi(argv[1]);
	unsigned int parametersNumber = argc;

	if (parametersNumber != 2)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: flipbyte.exe <input byte>\n";
		return 1;
	}

	if (inputByte < 0 || inputByte > 255)
	{
		cout << "The number must be greater than 0 and less than 255\n"; 
		return 1;
	}

	bitset<8> bitSequence(inputByte);
	const int bitSequenceLength = bitSequence.size() - 1;
	
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

	cout << bitSequence.to_ulong() << "\n";

	return 0;
}