#include "CLineSegment.h"

CLineSegment::CLineSegment(CPoint& startPoint, CPoint& endPoint, const std::string outlineColor)
	: m_startPoint(startPoint)
	, m_endPoint(endPoint)
	, m_outlineColor(outlineColor)
{
}

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return (sqrt(pow(m_endPoint.GetX() - m_startPoint.GetX(), 2) + pow(m_endPoint.GetY() - m_startPoint.GetY(), 2)));
}

std::string CLineSegment::GetOutlineColor() const
{
	return m_outlineColor;
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}