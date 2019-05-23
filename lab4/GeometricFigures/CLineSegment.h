#pragma once
#include "IShape.h"
#include "CPoint.h"

class CLineSegment : IShape
{
public:
	CLineSegment();
	~CLineSegment();
	double GetArea() const;
	double GetPerimeter() const;
	std::string ToString() const;
	std::string GetOutlineColor() const;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

};
