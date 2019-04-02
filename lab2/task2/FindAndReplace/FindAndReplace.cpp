#include "pch.h"
#include "FindAndReplace.h"

std::string FindAndReplace(std::string& subject, std::string& search, std::string& replace)
{
	size_t index = 0;
	while ((index = subject.find(search, index)) != std::string::npos)
	{
		subject.replace(index, search.length(), replace);
	}
	return subject;
}
