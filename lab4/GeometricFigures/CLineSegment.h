#pragma once
#include "IShape.h"
#include "CPoint.h"
#include <sstream>

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint& startPoint, CPoint& endPoint, const std::string outlineColor);
	~CLineSegment() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string GetOutlineColor() const override;
	void PrintInfo(std::ostream& output) const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	std::string m_outlineColor;
	CPoint m_startPoint;
	CPoint m_endPoint;
};
