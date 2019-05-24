#include "CRemoteControl.h"
#include "Shape.h"
#include "Const.h"
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
		std::string shape;
		ist >> shape;
		Shape figure;
		if (shape == figure.circle)
		{
		}
		else if (shape == figure.lineSegment)
		{
		}
		else if (shape == figure.rectangle)
		{
		}
		else if (shape == figure.triangle)
		{
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