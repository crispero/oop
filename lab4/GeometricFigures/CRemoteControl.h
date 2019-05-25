#pragma once
#include "CCircle.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "CLineSegment.h"
#include "IShape.h"
#include <sstream>
#include <memory>
#include <vector>

class CRemoteControl
{
public:
	CRemoteControl(std::istream& input, std::ostream& output);
	void HandleCommand();
	void PrintInfo();

private:
	std::shared_ptr<CCircle> CreateCircle(std::istringstream& ist);
	std::shared_ptr<CRectangle> CreateRectangle(std::istringstream& ist);
	std::shared_ptr<CTriangle> CreateTriangle(std::istringstream& ist);
	std::shared_ptr<CLineSegment> CreateLineSegment(std::istringstream& ist);

private:
	std::istream& m_input;
	std::ostream& m_output;

	std::vector<std::shared_ptr<IShape>> m_shape;
};
