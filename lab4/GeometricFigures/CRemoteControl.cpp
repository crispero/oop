#include "CRemoteControl.h"
#include "Const.h"
#include "Shape.h"
#include <sstream>

CRemoteControl::CRemoteControl(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void CRemoteControl::HandleCommand()
{
	std::string commandLine;
	while (std::getline(m_input, commandLine))
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

std::shared_ptr<CCircle> CRemoteControl::CreateCircle(std::istream& ist)
{
	double x, y, radius;
	std::string outlineColor, fillColor;

	ist >> x >> y >> radius;
	ist >> outlineColor >> fillColor;

	CPoint center(x, y);
	return std::make_shared<CCircle>(center, radius, outlineColor, fillColor);
}

std::shared_ptr<CRectangle> CRemoteControl::CreateRectangle(std::istream& ist)
{
	double x, y, width, height;
	std::string outlineColor, fillColor;

	ist >> x >> y >> width >> height;
	ist >> outlineColor >> fillColor;

	CPoint leftTop(x, y);
	return std::make_shared<CRectangle>(leftTop, width, height, outlineColor, fillColor);
}

std::shared_ptr<CTriangle> CRemoteControl::CreateTriangle(std::istream& ist)
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

std::shared_ptr<CLineSegment> CRemoteControl::CreateLineSegment(std::istream& ist)
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

std::shared_ptr<IShape> CRemoteControl::GetShapeWithMaxArea()
{
	return *std::max_element(m_shape.begin(), m_shape.end(), [](const std::shared_ptr<IShape>& shape1, const std::shared_ptr<IShape>& shape2) -> bool { return shape1->GetArea() < shape2->GetArea(); });
}

void CRemoteControl::PrintShapeWithMaxArea()
{
	m_output << SHAPE_WITH_MAX_AREA;
	GetShapeWithMaxArea()->PrintInfo(m_output);
	m_output << LINE_BREAK_CHARACTER;
}

void CRemoteControl::PrintShapeWithMinPerimeter()
{
	m_output << SHAPE_WITH_MIN_PERIMETER;
	GetShapeWithMinPerimeter()->PrintInfo(m_output);
	m_output << LINE_BREAK_CHARACTER;
}

std::shared_ptr<IShape> CRemoteControl::GetShapeWithMinPerimeter()
{
	return *std::min_element(m_shape.begin(), m_shape.end(), [](const std::shared_ptr<IShape>& shape1, const std::shared_ptr<IShape>& shape2) -> bool { return shape1->GetPerimeter() < shape2->GetPerimeter(); });
}

void CRemoteControl::PrintInfo()
{
	if (m_shape.size() == 0)
	{
		m_output << ERROR_NO_FIGURES_FOUND;
	}
	else if (m_shape.size() == 1)
	{
		m_shape[0]->PrintInfo(m_output);
	}
	else
	{
		PrintShapeWithMaxArea();
		PrintShapeWithMinPerimeter();
	}
}