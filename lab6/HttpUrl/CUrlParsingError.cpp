#include "CUrlParsingError.h"
#include <iostream>

CUrlParsingError::CUrlParsingError(std::string const& message)
	: std::invalid_argument(message)
{
}

CUrlParsingError::~CUrlParsingError()
{
}
