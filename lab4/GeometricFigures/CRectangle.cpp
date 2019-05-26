#include "CRectangle.h"
#include "Const.h"

CRectangle::CRectangle(CPoint& leftTop, const double width, const double height, const std::string outlineColor, const std::string fillColor)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, m_outlineColor(outlineColor)
	, m_fillColor(fillColor)
{
}

double CRectangle::GetArea() const
{
	return m_height * m_width;
}

double CRectangle::GetPerimeter() const
{
	return (m_height + m_width) * 2;
}

std::string CRectangle::GetOutlineColor() const
{
	return m_outlineColor;
}

std::string CRectangle::GetFillColor() const
{
	return m_fillColor;
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightBottom() const
{
	CPoint rightBottom(m_leftTop.GetX() + m_width, m_leftTop.GetY() + m_height);
	return rightBottom;
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::PrintInfo(std::ostream& output) const
{
	output << AREA << GetArea() << LINE_BREAK_CHARACTER;
	output << PERIMETER << GetPerimeter() << LINE_BREAK_CHARACTER;
	output << OUTLINE_COLOR << GetOutlineColor() << LINE_BREAK_CHARACTER;
	output << FILL_COLOR << GetFillColor() << LINE_BREAK_CHARACTER;
	output << LEFT_TOP << GetLeftTop().GetX() << SPACE << GetLeftTop().GetY() << LINE_BREAK_CHARACTER;
	output << RIGHT_BOTTOM << GetRightBottom().GetX() << SPACE << GetRightBottom().GetY() << LINE_BREAK_CHARACTER;
	output << WIDTH << GetWidth() << LINE_BREAK_CHARACTER;
	output << HEIGHT << GetHeight() << LINE_BREAK_CHARACTER;
}