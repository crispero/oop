#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CCircle : ISolidShape
{
public:
	CCircle(CPoint& m_center, const double radius, const std::string outlineColor, const std::string fillColor);
	double GetArea() const;
	double GetPerimeter() const;
	std::string GetOutlineColor() const;
	std::string GetFillColor() const;

	CPoint GetCenter() const;
	double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
	std::string m_outlineColor;
	std::string m_fillColor;
};
