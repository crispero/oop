#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CTriangle : ISolidShape
{
public:
	CTriangle(CPoint& vertex1, CPoint& vertex2, CPoint& vertex3, const std::string outlineColor, const std::string fillColor);
	double GetArea() const;
	double GetPerimeter() const;
	std::string GetOutlineColor() const;
	std::string GetFillColor() const;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	std::string m_outlineColor;
	std::string m_fillColor;
	
};
