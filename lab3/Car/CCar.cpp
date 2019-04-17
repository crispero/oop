#include "pch.h"
#include "CCar.h"
#include <iostream>

CCar::CCar()
:m_gear(0)
,m_isTurnOnEngine("off")
,m_speed(0)
,m_direction("stop")
{}

CCar::~CCar()
{}

bool CCar::TurnOnEngine()
{
	if (m_isTurnOnEngine == "off") 
	{
		m_isTurnOnEngine = "on";
		std::cout << "Engine on" << std::endl;
		return true;
	}
	std::cout << "Engine is already on" << std::endl;
	return false;
}

bool CCar::TurnOffEngine()
{
	if (m_gear == 0 && m_speed == 0)
	{
		m_isTurnOnEngine = "off";
		std::cout << "Engine off" << std::endl;
		return true;
	}
	std::cout << "Engine is already off" << std::endl;
	return false;
}

bool CCar::SetGear(int gear)
{
	switch (gear)
	{
	case -1:
		if (m_speed == 0)
		{
			m_gear = gear;
			m_direction = "back";
			return true;
		}
		break;
	}
		
	return true;
}

bool CCar::SetSpeed(int speed)
{
	return true;
}

void CCar::GetCurrentInfo()
{
	std::cout << "Engine condition: " << m_isTurnOnEngine << std::endl;
	std::cout << "Direction of travel: " << m_direction << std::endl;
	std::cout << "Speed: " << m_speed << std::endl;
	std::cout << "Gear: " << m_gear << std::endl;
}