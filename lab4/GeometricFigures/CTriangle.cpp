#include "CTriangle.h"

CTriangle::CTriangle(CPoint& vertex1, CPoint& vertex2, CPoint& vertex3, const std::string outlineColor, const std::string fillColor)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CTriangle::GetSide(CPoint firstVertex, CPoint secondVertex) const
{
	return (sqrt(pow(secondVertex.GetX - firstVertex.GetX, 2) + pow(secondVertex.GetY - firstVertex.GetY, 2)));
}

double CTriangle::GetArea() const
{
	double firstSide = GetSide(m_vertex1, m_vertex2);
	double secondSide = GetSide(m_vertex2, m_vertex3);
	double thirdSide = GetSide(m_vertex3, m_vertex1);

	double halfPerimeter = (firstSide + secondSide + thirdSide) / 2;
	double area = sqrt(halfPerimeter * (halfPerimeter - firstSide) * (halfPerimeter - secondSide) * (halfPerimeter - thirdSide));
	return area;
}

double CTriangle::GetPerimeter() const
{
	double firstSide = GetSide(m_vertex1, m_vertex2);
	double secondSide = GetSide(m_vertex2, m_vertex3);
	double thirdSide = GetSide(m_vertex3, m_vertex1);

	double perimeter = firstSide + secondSide + thirdSide;
	return perimeter;
}

std::string CTriangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CTriangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}