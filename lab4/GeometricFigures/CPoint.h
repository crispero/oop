#pragma once

class CPoint
{
public:
	CPoint(double const x, double const y);
	double GetX() const;
	double GetY() const;

private:
	double m_x;
	double m_y;
};
