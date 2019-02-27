#include "pch.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool FindStringInStream(ifstream& fin, string givenString)
{
	string line;
	bool found = false;
	for (int lineIndex = 1; getline(fin, line); lineIndex++)
	{
		if (line.find(givenString) != string::npos)
		{
			found = true;
			cout << "Line index: " << lineIndex << "\n";
		}
	}

	return found;
}

int main(int argc, char* argv[])
{
	string fileName = argv[1];
	string givenString = argv[2];
	int parametersNumber = argc;

	ifstream fin(fileName);

	if (parametersNumber < 3 || parametersNumber > 3)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: findtext.txt <file name> <text to search>\n";
		return 1;
	}

	if (!fin.is_open())
	{
		cout << "Failed to open " << fileName << " for reading\n";
		return 1;
	}

	if (givenString == "")
	{
		cout << "Given string is empty\n";
		return 1;
	}

	if (!FindStringInStream(fin, givenString))
	{
		cout << "Text not found\n";
		return 1;
	}

	return 0;
}