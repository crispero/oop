#include "CRemoteControl.h"
#include "Const.h"
#include "UserCommand.h"
#include <iostream>

CRemoteControl::CRemoteControl(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
{
}

void CRemoteControl::HandleCommand()
{
	std::string commandLine;
	UserCommand userCommand;

	while (m_input >> commandLine)
	{	
		if (commandLine == userCommand.Info)
		{
			PrintInfo(m_car);
		}
		else if (commandLine == userCommand.EngineOn)
		{
			m_output << (m_car.TurnOnEngine() ? ENGINE_ON : ENGINE_ALREADY_ON);
		}
		else if (commandLine == userCommand.EngineOff)
		{
			m_output << (m_car.TurnOffEngine() ? ENGINE_OFF : ENGINE_ALREADY_OFF);
		}
		else if (commandLine == userCommand.SetGear)
		{
			SetGear(m_car);
		}
		else if (commandLine == userCommand.SetSpeed)
		{
			SetSpeed(m_car);
		}
		else
		{
			m_output << UNKNOWN_COMMAND;
		}

		m_output << std::endl;
	}
}

bool CRemoteControl::isNumber(int& speed)
{
	try
	{
		std::string num;
		m_input >> num;
		speed = std::stoi(num);
		return true;
	}
	catch (const std::invalid_argument&)
	{
		return false;
	}
}

void CRemoteControl::SetGear(CCar& car)
{
	int gear;

	if (!isNumber(gear))
	{
		m_output << ERROR_GEAR_NOT_NUM << std::endl;
	}

	if (car.SetGear(gear))
	{
		m_output << GEAR_WAS_CHANGED << gear << std::endl;
	}
	else
	{
		m_output << CANT_CHANGE_GEAR << std::endl;
	}
}

void CRemoteControl::SetSpeed(CCar& car)
{
	int speed;

	if (!isNumber(speed))
	{
		m_output << ERROR_SPEED_NOT_NUM << std::endl;
	}

	if (car.SetSpeed(speed))
	{
		m_output << SPEED_WAS_CHANGED << speed << std::endl;
	}
	else
	{
		m_output << CANT_CHANGE_SPEED << std::endl;
	}
}

void CRemoteControl::PrintInfo(CCar& car)
{
	m_output << ENGINE_CONDITION << car.GetEngine() << std::endl;
	m_output << DIRECTION_OF_TRAVEL << car.GetDirection() << std::endl;
	m_output << SPEED << car.GetSpeed() << std::endl;
	m_output << GEAR << car.GetGear() << std::endl;
}
