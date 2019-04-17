#pragma once
#include <string>

class CCar
{
public:
	CCar();
	~CCar();
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);
	void GetCurrentInfo();

private:
	std::string m_isTurnOnEngine;
	std::string m_direction;
	int m_speed;
	int m_gear;
};
