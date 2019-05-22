#pragma once
#include "CCar.h"
#include <sstream>

class CRemoteControl
{
public:
	CRemoteControl(CCar& car, std::istream& input, std::ostream& output);
	void HandleCommand();

private:
	void SetGear(CCar& car);
	void SetSpeed(CCar& car);
	void PrintInfo(CCar& car);
	bool isNumber(int& speed);

private:
	CCar& m_car;
	std::istream& m_input;
	std::ostream& m_output;
};
