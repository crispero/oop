#include "CRemoteControl.h"
#include <iostream>

CRemoteControl::CRemoteControl(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
{
}

void CRemoteControl::HandleCommand()
{

}

void CRemoteControl::PrintInfo()
{
}