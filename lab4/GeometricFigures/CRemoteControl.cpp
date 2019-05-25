#include "CRemoteControl.h"
#include "Const.h"
#include "Shape.h"
#include <iostream>
#include <string>

CRemoteControl::CRemoteControl(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void CRemoteControl::HandleCommand()
{
	std::string commandLine;
	while (getline(m_input, commandLine))
	{
		std::istringstream ist(commandLine);
		std::string shapeName;
		ist >> shapeName;
		Shape figure;
		std::shared_ptr<IShape> shape;

		if (shapeName == figure.circle)
		{
			shape = CreateCircle(ist);
			m_shape.push_back(shape);
		}
		else if (shapeName == figure.rectangle)
		{
			shape = CreateRectangle(ist);
			m_shape.push_back(shape);
		}
		else if (shapeName == figure.triangle)
		{
			shape = CreateTriangle(ist);
			m_shape.push_back(shape);
		}
		else if (shapeName == figure.lineSegment)
		{
			shape = CreateLineSegment(ist);
			m_shape.push_back(shape);
		}
		else
		{
			m_output << ERROR_UNKNOWN_FIGURE << std::endl;
		}
	}
}

void CRemoteControl::PrintInfo()
{
}

std::shared_ptr<CCircle> CRemoteControl::CreateCircle(std::istringstream& ist)
{
	double x, y, radius;
	std::string outlineColor, fillColor;

	ist >> x >> y >> radius;
	ist >> outlineColor >> fillColor;

	CPoint center(x, y);
	return std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
}

std::shared_ptr<CRectangle> CRemoteControl::CreateRectangle(std::istringstream& ist)
{
	double x, y, width, height;
	std::string outlineColor, fillColor;

	ist >> x >> y >> width >> height;
	ist >> outlineColor >> fillColor;

	CPoint leftTop(x, y);
	return std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor);
}

std::shared_ptr<CTriangle> CRemoteControl::CreateTriangle(std::istringstream& ist)
{
	double x1, y1;
	double x2, y2;
	double x3, y3;
	std::string outlineColor, fillColor;

	ist >> x1 >> y1;
	ist >> x2 >> y2;
	ist >> x3 >> y3;
	ist >> outlineColor >> fillColor;

	CPoint vertex1(x1, y1);
	CPoint vertex2(x2, y2);
	CPoint vertex3(x3, y3);

	return std::make_shared<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
}

std::shared_ptr<CLineSegment> CRemoteControl::CreateLineSegment(std::istringstream& ist)
{
	double x1, y1;
	double x2, y2;
	std::string outlineColor;

	ist >> x1 >> y1;
	ist >> x2 >> y2;
	ist >> outlineColor;

	CPoint startPoint(x1, y1);
	CPoint endPoint(x2, y2);

	return std::make_shared<CLineSegment>(startPoint, endPoint, outlineColor);
}