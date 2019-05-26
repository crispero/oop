#include "CLineSegment.h"
#include "Const.h"

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

void CLineSegment::PrintInfo(std::ostream& output) const
{
	output << AREA << GetArea() << LINE_BREAK_CHARACTER;
	output << PERIMETER << GetPerimeter() << LINE_BREAK_CHARACTER;
	output << OUTLINE_COLOR << GetOutlineColor() << LINE_BREAK_CHARACTER;
	output << START_POINT << GetStartPoint().GetX() << SPACE << GetStartPoint().GetY() << LINE_BREAK_CHARACTER;
	output << END_POINT << GetEndPoint().GetX() << SPACE << GetEndPoint().GetY() << LINE_BREAK_CHARACTER;
}