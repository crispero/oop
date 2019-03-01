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
	int parametersNumber = argc;

	if (parametersNumber != 3)
	{
		cerr << "Invalid arguments count\n"
			 << "Usage: findtext.exe <file name> <text to search>\n";
		return 1;
	}

	string fileName = argv[1];
	string givenString = argv[2];
	
	ifstream fin(fileName);

	if (!fin.is_open())
	{
		cerr << "Failed to open " << fileName << " for reading\n";
		return 1;
	}

	if (givenString == "")
	{
		cerr << "Given string is empty\n";
		return 1;
	}

	if (!FindStringInStream(fin, givenString))
	{
		cerr << "Text not found\n";
		return 1;
	}

	return 0;
}