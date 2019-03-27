#include "pch.h"
#include <iostream>
#include <string>

const std::string INVALID_ARGUMENTS_COUNT = "Invalid arguments count\nUsage: findAndReplace.exe <search-string> <replace string>\n";
const std::string EMPTY_SUBJECT_STRING = "Search string is empty\n";

std::string FindAndReplace(std::string& subject, std::string& search, std::string& replace)
{
	size_t index = 0;
	while ((index = subject.find(search, index)) != std::string::npos)
	{
		subject.replace(index, search.length(), replace);
	}
	return subject;
}

int main(int argc, char *argv[])
{
	int argumentsNumber = argc;
	if (argumentsNumber != 3)
	{
		std::cout << INVALID_ARGUMENTS_COUNT;
		return 1;
	}

	std::string subject;
	std::string search = argv[1];
	std::string replace = argv[2];

	while (!std::cin.eof())
	{
		getline(std::cin, subject);
		if (subject.size() == 0)
		{
			std::cout << EMPTY_SUBJECT_STRING;
		}
		else
		{
			std::cout << FindAndReplace(subject, search, replace) << std::endl;
		}
	}
}
