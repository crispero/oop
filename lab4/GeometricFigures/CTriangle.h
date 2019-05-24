#pragma once
#include "ISolidShape.h"
#include "CPoint.h"

class CTriangle : ISolidShape
{
public:
	CTriangle(CPoint& vertex1, CPoint& vertex2, CPoint& vertex3, const std::string outlineColor, const std::string fillColor);
	~CTriangle() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string GetOutlineColor() const override;
	std::string GetFillColor() const override;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

private:
	double GetSide(CPoint firstVertex, CPoint secondVertex) const; 

	CPoint m_vertex1;
	CPoint m_vertex2;
	CPoint m_vertex3;
	std::string m_outlineColor;
	std::string m_fillColor;
	
};
