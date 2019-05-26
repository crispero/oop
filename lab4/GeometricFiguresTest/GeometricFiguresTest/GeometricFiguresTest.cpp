#define CATCH_CONFIG_MAIN
#define _USE_MATH_DEFINES
#include "lab4/GeometricFigures/CCircle.h"
#include "lab4/GeometricFigures/CLineSegment.h"
#include "lab4/GeometricFigures/CPoint.h"
#include "lab4/GeometricFigures/CRectangle.h"
#include "lab4/GeometricFigures/CRemoteControl.h"
#include "lab4/GeometricFigures/CTriangle.h"
#include <catch2/catch.hpp>
#include <cmath>

TEST_CASE("CCircle")
{
	SECTION("CCircle standard")
	{
		CPoint center(0.0, 0.0);
		double radius = 4.0;
		std::string outlineColor = "ff0000", fillColor = "00ff00";
		CCircle circle(center, radius, outlineColor, fillColor);

		CHECK(circle.GetArea() == M_PI * 4.0 * 4.0);
		CHECK(circle.GetPerimeter() == 2 * M_PI * 4.0);
		CHECK(circle.GetOutlineColor() == "ff0000");
		CHECK(circle.GetFillColor() == "00ff00");
		CHECK(circle.GetCenter().GetX() == center.GetX());
		CHECK(circle.GetCenter().GetY() == center.GetY());
		CHECK(circle.GetRadius() == 4.0);

		std::stringstream output;
		std::stringstream correctOutput("Area: 50.2655\nPerimeter: 25.1327\nOutline color: ff0000\nFill color: 00ff00\nCenter: 0 0\nRadius: 4\n");

		circle.PrintInfo(output);
		CHECK(output.str() == correctOutput.str());
	}

	SECTION("CCircle with zero radius")
	{
		CPoint center(4.0, 4.0);
		double radius = 0.0;
		std::string outlineColor = "ff0000", fillColor = "00ff00";
		CCircle circle(center, radius, outlineColor, fillColor);

		CHECK(circle.GetArea() == M_PI * 0.0 * 0.0);
		CHECK(circle.GetPerimeter() == 2 * M_PI * 0.0);
		CHECK(circle.GetOutlineColor() == "ff0000");
		CHECK(circle.GetFillColor() == "00ff00");
		CHECK(circle.GetCenter().GetX() == center.GetX());
		CHECK(circle.GetCenter().GetY() == center.GetY());
		CHECK(circle.GetRadius() == 0.0);

		std::stringstream output;
		std::stringstream correctOutput("Area: 0\nPerimeter: 0\nOutline color: ff0000\nFill color: 00ff00\nCenter: 4 4\nRadius: 0\n");

		circle.PrintInfo(output);
		CHECK(output.str() == correctOutput.str());
	}
}

TEST_CASE("CLineSegment")
{
	SECTION("CLineSegment standard")
	{
		CPoint startPoint(2.0, 0.0);
		CPoint endPoint(2.0, 4.0);
		std::string outlineColor = "00ff00";
		CLineSegment lineSegment(startPoint, endPoint, outlineColor);

		CHECK(lineSegment.GetArea() == 0);
		CHECK(lineSegment.GetPerimeter() == 4.0);
		CHECK(lineSegment.GetStartPoint().GetX() == startPoint.GetX());
		CHECK(lineSegment.GetStartPoint().GetY() == startPoint.GetY());
		CHECK(lineSegment.GetEndPoint().GetX() == endPoint.GetX());
		CHECK(lineSegment.GetEndPoint().GetY() == endPoint.GetY());
		CHECK(lineSegment.GetOutlineColor() == "00ff00");

		std::stringstream output;
		std::stringstream correctOutput("Area: 0\nPerimeter: 4\nOutline color: 00ff00\nStart point: 2 0\nEnd point: 2 4\n");

		lineSegment.PrintInfo(output);
		CHECK(output.str() == correctOutput.str());
	}

	SECTION("CLineSegment is point")
	{
		CPoint startPoint(0.0, 0.0);
		CPoint endPoint(0.0, 0.0);
		std::string outlineColor = "00ff00";
		CLineSegment lineSegment(startPoint, endPoint, outlineColor);

		CHECK(lineSegment.GetArea() == 0);
		CHECK(lineSegment.GetPerimeter() == 0.0);
		CHECK(lineSegment.GetStartPoint().GetX() == startPoint.GetX());
		CHECK(lineSegment.GetStartPoint().GetY() == startPoint.GetY());
		CHECK(lineSegment.GetEndPoint().GetX() == endPoint.GetX());
		CHECK(lineSegment.GetEndPoint().GetY() == endPoint.GetY());
		CHECK(lineSegment.GetOutlineColor() == "00ff00");

		std::stringstream output;
		std::stringstream correctOutput("Area: 0\nPerimeter: 0\nOutline color: 00ff00\nStart point: 0 0\nEnd point: 0 0\n");

		lineSegment.PrintInfo(output);
		CHECK(output.str() == correctOutput.str());
	}
}

TEST_CASE("CRectangle")
{
	SECTION("CRectangle standard test")
	{
		CPoint leftTop(5.0, 0.0);
		double width = 10.0, height = 5.0;
		std::string outlineColor = "00ff00", fillColor = "000ff0";
		CPoint rightBottom(leftTop.GetX() + width, leftTop.GetY() + height);
		CRectangle rectangle(leftTop, width, height, outlineColor, fillColor);

		CHECK(rectangle.GetArea() == width * height);
		CHECK(rectangle.GetPerimeter() == ((width + height) * 2));
		CHECK(rectangle.GetOutlineColor() == "00ff00");
		CHECK(rectangle.GetFillColor() == "000ff0");
		CHECK(rectangle.GetLeftTop().GetX() == leftTop.GetX());
		CHECK(rectangle.GetLeftTop().GetY() == leftTop.GetY());
		CHECK(rectangle.GetRightBottom().GetX() == rightBottom.GetX());
		CHECK(rectangle.GetRightBottom().GetY() == rightBottom.GetY());
		CHECK(rectangle.GetWidth() == width);
		CHECK(rectangle.GetHeight() == height);

		std::stringstream output;
		std::stringstream correctOutput("Area: 50\nPerimeter: 30\nOutline color: 00ff00\nFill color: 000ff0\nLeft top: 5 0\nRight bottom: 15 5\nWidth: 10\nHeight: 5\n");

		rectangle.PrintInfo(output);
		CHECK(output.str() == correctOutput.str());
	}

	SECTION("CRectangle with zero width")
	{
		CPoint leftTop(5.0, 0.0);
		double width = 0.0, height = 5.0;
		std::string outlineColor = "00ff00", fillColor = "000ff0";
		CPoint rightBottom(leftTop.GetX() + width, leftTop.GetY() + height);
		CRectangle rectangle(leftTop, width, height, outlineColor, fillColor);

		CHECK(rectangle.GetArea() == width * height);
		CHECK(rectangle.GetPerimeter() == ((width + height) * 2));
		CHECK(rectangle.GetOutlineColor() == "00ff00");
		CHECK(rectangle.GetFillColor() == "000ff0");
		CHECK(rectangle.GetLeftTop().GetX() == leftTop.GetX());
		CHECK(rectangle.GetLeftTop().GetY() == leftTop.GetY());
		CHECK(rectangle.GetRightBottom().GetX() == rightBottom.GetX());
		CHECK(rectangle.GetRightBottom().GetY() == rightBottom.GetY());
		CHECK(rectangle.GetWidth() == width);
		CHECK(rectangle.GetHeight() == height);

		std::stringstream output;
		std::stringstream correctOutput("Area: 0\nPerimeter: 10\nOutline color: 00ff00\nFill color: 000ff0\nLeft top: 5 0\nRight bottom: 5 5\nWidth: 0\nHeight: 5\n");

		rectangle.PrintInfo(output);
		CHECK(output.str() == correctOutput.str());
	}
}

TEST_CASE("CTriangle")
{
	SECTION("CTriangle standard test")
	{
		CPoint vertex1(0.0, 0.0);
		CPoint vertex2(0.0, 3.0);
		CPoint vertex3(4.0, 3.0);
		std::string outlineColor = "00ff00", fillColor = "000ff0";
		CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

		CHECK(triangle.GetArea() == 6.0);
		CHECK(triangle.GetPerimeter() == 12.0);
		CHECK(triangle.GetOutlineColor() == "00ff00");
		CHECK(triangle.GetFillColor() == "000ff0");
		CHECK(triangle.GetVertex1().GetX() == vertex1.GetX());
		CHECK(triangle.GetVertex1().GetY() == vertex1.GetX());
		CHECK(triangle.GetVertex2().GetX() == vertex2.GetX());
		CHECK(triangle.GetVertex2().GetY() == vertex2.GetY());
		CHECK(triangle.GetVertex3().GetX() == vertex3.GetX());
		CHECK(triangle.GetVertex3().GetY() == vertex3.GetY());

		std::stringstream output;
		std::stringstream correctOutput("Area: 6\nPerimeter: 12\nOutline color: 00ff00\nFill color: 000ff0\nVertex1: 0 0\nVertex2: 0 3\nVertex2: 4 3\n");

		triangle.PrintInfo(output);
		CHECK(output.str() == correctOutput.str());
	}

	SECTION("CTriangle incorrect")
	{
		CPoint vertex1(0.0, 0.0);
		CPoint vertex2(3.0, 0.0);
		CPoint vertex3(8.0, 0.0);
		std::string outlineColor = "00ff00", fillColor = "000ff0";
		CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

		CHECK(triangle.GetArea() == 0.0);
		CHECK(triangle.GetPerimeter() == 16.0);
		CHECK(triangle.GetOutlineColor() == "00ff00");
		CHECK(triangle.GetFillColor() == "000ff0");
		CHECK(triangle.GetVertex1().GetX() == vertex1.GetX());
		CHECK(triangle.GetVertex1().GetY() == vertex1.GetX());
		CHECK(triangle.GetVertex2().GetX() == vertex2.GetX());
		CHECK(triangle.GetVertex2().GetY() == vertex2.GetY());
		CHECK(triangle.GetVertex3().GetX() == vertex3.GetX());
		CHECK(triangle.GetVertex3().GetY() == vertex3.GetY());

		std::stringstream output;
		std::stringstream correctOutput("Area: 0\nPerimeter: 16\nOutline color: 00ff00\nFill color: 000ff0\nVertex1: 0 0\nVertex2: 3 0\nVertex2: 8 0\n");

		triangle.PrintInfo(output);
		CHECK(output.str() == correctOutput.str());
	}
}

TEST_CASE("CPoint")
{
	CPoint point1(3.0, 4.0);
	CHECK(point1.GetX() == 3.0);
	CHECK(point1.GetY() == 4.0);

	CPoint point2(0.251, 16.321);
	CHECK(point2.GetX() == 0.251);
	CHECK(point2.GetY() == 16.321);
}

TEST_CASE("CRemoteControl")
{
	SECTION("CCircle")
	{
		std::stringstream input("circle 4.0 4.0 8.2 ff0000 00ff00");
		std::stringstream output;
		std::stringstream correctOutput("Area: 211.241\nPerimeter: 51.5221\nOutline color: ff0000\nFill color: 00ff00\nCenter: 4 4\nRadius: 8.2\n");

		CRemoteControl remoteControl(input, output);
		remoteControl.HandleCommand();
		remoteControl.PrintInfo();

		CHECK(output.str() == correctOutput.str());
	}

	SECTION("CLineSegment")
	{
		std::stringstream input("lineSegment 0.0 0.0 0.0 -6.0 ff0000");
		std::stringstream output;
		std::stringstream correctOutput("Area: 0\nPerimeter: 6\nOutline color: ff0000\nStart point: 0 0\nEnd point: 0 -6\n");

		CRemoteControl remoteControl(input, output);
		remoteControl.HandleCommand();
		remoteControl.PrintInfo();

		CHECK(output.str() == correctOutput.str());
	}

	SECTION("CRectangle")
	{
		std::stringstream input("rectangle 0.0 4.0 8.0 4.0 ff0000 00ff00");
		std::stringstream output;
		std::stringstream correctOutput("Area: 32\nPerimeter: 24\nOutline color: ff0000\nFill color: 00ff00\nLeft top: 0 4\nRight bottom: 8 8\nWidth: 8\nHeight: 4\n");

		CRemoteControl remoteControl(input, output);
		remoteControl.HandleCommand();
		remoteControl.PrintInfo();

		CHECK(output.str() == correctOutput.str());
	}

	SECTION("CTriangle")
	{
		std::stringstream input("triangle 0.0 0.0 0.0 3.0 4.0 3.0 ff0000 00ff00");
		std::stringstream output;
		std::stringstream correctOutput("Area: 6\nPerimeter: 12\nOutline color: ff0000\nFill color: 00ff00\nVertex1: 0 0\nVertex2: 0 3\nVertex2: 4 3\n");

		CRemoteControl remoteControl(input, output);
		remoteControl.HandleCommand();
		remoteControl.PrintInfo();

		CHECK(output.str() == correctOutput.str());
	}

	SECTION("PrintInfo")
	{
		std::stringstream input("circle 4.0 4.0 8.2 ff0000 00ff00\nlineSegment 0.0 0.0 0.0 -6.0 ff0000\nrectangle 0.0 4.0 8.0 4.0 ff0000 00ff00\ntriangle 0.0 0.0 0.0 3.0 4.0 3.0 ff0000 00ff00");
		std::stringstream output;
		std::stringstream correctOutput("Shape with max area:\nArea: 211.241\nPerimeter: 51.5221\nOutline color: ff0000\nFill color: 00ff00\nCenter: 4 4\nRadius: 8.2\n\nShape with min perimeter:\nArea: 0\nPerimeter: 6\nOutline color: ff0000\nStart point: 0 0\nEnd point: 0 -6\n\n");

		CRemoteControl remoteControl(input, output);
		remoteControl.HandleCommand();
		remoteControl.PrintInfo();

		CHECK(output.str() == correctOutput.str());
	}

	SECTION("Unknown figure")
	{
		std::stringstream input("triangl 0.0 0.0 0.0 3.0 4.0 3.0 ff0000 00ff00");
		std::stringstream output;
		std::stringstream correctOutput("Unknown figure\nNo figures found");

		CRemoteControl remoteControl(input, output);
		remoteControl.HandleCommand();
		remoteControl.PrintInfo();

		CHECK(output.str() == correctOutput.str());
	}

	SECTION("Empty input")
	{
		std::stringstream input("");
		std::stringstream output;
		std::stringstream correctOutput("No figures found");

		CRemoteControl remoteControl(input, output);
		remoteControl.HandleCommand();
		remoteControl.PrintInfo();

		CHECK(output.str() == correctOutput.str());
	}
}