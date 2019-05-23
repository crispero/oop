#pragma once
#include "IShape.h"

class ISolidShape : IShape
{
public:
	virtual std::string GetFillColor() const = 0;
};