#pragma once
#include <string>
#include <stdexcept>

class CUrlParsingError : public std::invalid_argument
{
public:
	CUrlParsingError(std::string const& message);
	~CUrlParsingError();
};
