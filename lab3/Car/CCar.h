#pragma once
#include "Direction.h"
#include "Gear.h"
#include "SpeedRangeForGear.h"
#include <string>

class CCar
{
public:
	CCar();
	~CCar();

	std::string GetDirection() const;
	bool GetTurnEngine() const;
	std::string GetEngine() const;
	std::string GetGear() const;
	int GetSpeed() const;

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

private:
	bool UpdateSpeedAndDirection(int speed, SpeedRangeForGear speedRange, Direction direction);
	bool UpdateGear(int gear, SpeedRangeForGear speedRange, Direction direction);

	bool m_isEngineOn = false;
	Direction m_direction = Direction::Stop;
	int m_speed = 0;
	Gear m_gear = Gear::NEUTRAL;
};
