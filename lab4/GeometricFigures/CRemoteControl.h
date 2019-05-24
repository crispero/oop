#pragma once
#include <sstream>

class CRemoteControl
{
public:
	CRemoteControl(std::istream& input, std::ostream& output);
	void HandleCommand();
	void PrintInfo();

private:
	std::istream& m_input;
	std::ostream& m_output;
};
