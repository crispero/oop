#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CRectangle : ISolidShape
{
public:
	CRectangle(CPoint& leftTop, const double width, const double height, const std::string outlineColor, const std::string fillColor);
	double GetArea() const;
	double GetPerimeter() const;
	std::string GetOutlineColor() const;
	std::string GetFillColor() const;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

private:
	double m_width;
	double m_height;
	CPoint m_leftTop;
	std::string m_outlineColor;
	std::string m_fillColor;

};
