#define _USE_MATH_DEFINES
#include "CCircle.h"
#include "Const.h"
#include <cmath>

CCircle::CCircle(CPoint& center, const double radius, const std::string outlineColor, const std::string fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CCircle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::PrintInfo(std::ostream& output) const 
{
	output << AREA << GetArea() << LINE_BREAK_CHARACTER;
	output << PERIMETER << GetPerimeter() << LINE_BREAK_CHARACTER;
	output << OUTLINE_COLOR << GetOutlineColor() << LINE_BREAK_CHARACTER;
	output << FILL_COLOR << GetFillColor() << LINE_BREAK_CHARACTER;
	output << CENTER << GetCenter().GetX() << SPACE << GetCenter().GetY() << LINE_BREAK_CHARACTER;
	output << RADIUS << GetRadius() << LINE_BREAK_CHARACTER;
}