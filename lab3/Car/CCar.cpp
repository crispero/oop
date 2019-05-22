#include "pch.h"
#include "CCar.h"
#include "Const.h"

CCar::CCar()
{
}

CCar::~CCar()
{
}

std::string CCar::GetDirection() const
{
	switch (m_direction)
	{
	case Direction::Stop:
		return STOP;
	case Direction::Forward:
		return FORWARD;
	case Direction::Backward:
		return BACKWARD;
	default:
		return "Undefined";
	}
}

bool CCar::GetTurnEngine() const
{
	return m_isEngineOn;
}

std::string CCar::GetEngine() const
{
	return GetTurnEngine() ? "On" : "Off";
}

std::string CCar::GetGear() const
{
	switch (m_gear)
	{
	case Gear::REVERSE:
		return "Reverse";
	case Gear::NEUTRAL:
		return "Neutral";
	case Gear::FIRST:
		return "First";
	case Gear::SECOND:
		return "Second";
	case Gear::THIRD:
		return "Third";
	case Gear::FOURTH:
		return "Fourth";
	case Gear::FIFTH:
		return "Fifth";
	default:
		return ERROR_UNKNOWN_GEAR;
	}
}

int CCar::GetSpeed() const
{
	return m_speed;
}

bool CCar::TurnOnEngine()
{
	if (!m_isEngineOn)
	{
		m_isEngineOn = true;
		return true;
	}

	return false;
}

bool CCar::TurnOffEngine()
{
	if (m_isEngineOn && m_gear == Gear::NEUTRAL && m_speed == 0)
	{
		m_isEngineOn = false;
		return true;
	}

	return false;
}

bool CCar::UpdateGear(int gear, SpeedRangeForGear speedRange, Direction direction)
{
	bool isParamsAreValid = (direction == m_direction) && (m_speed >= speedRange.min_speed) && (m_speed <= speedRange.max_speed);

	if (isParamsAreValid)
	{
		m_gear = Gear(gear);
		return true;
	}

	return false;
}

bool CCar::SetGear(int gear)
{
	if (!m_isEngineOn)
	{
		if (gear == 0)
		{
			m_gear = Gear::NEUTRAL;
			return true;
		}

		return false;
	}

	switch (gear)
	{
	case -1:
		return UpdateGear(-1, ZERO_SPEED, Direction::Stop);
	case 0:
		m_gear = Gear::NEUTRAL;
		return true;
	case 1:
		return UpdateGear(1, FIRST_SPEED, Direction::Forward) || UpdateGear(1, ZERO_SPEED, Direction::Stop);
	case 2:
		return UpdateGear(2, SECOND_SPEED, Direction::Forward);
	case 3:
		return UpdateGear(3, THIRD_SPEED, Direction::Forward);
	case 4:
		return UpdateGear(4, FOURTH_SPEED, Direction::Forward);
	case 5:
		return UpdateGear(5, FIFTH_SPEED, Direction::Forward);
	default:
		return false;
	}
}

bool CCar::UpdateSpeedAndDirection(int speed, SpeedRangeForGear speedRange, Direction direction)
{
	bool isSpeedRange = (speed >= speedRange.min_speed) && (speed <= speedRange.max_speed);

	if (isSpeedRange)
	{
		m_speed = speed;
		m_direction = direction;
		return true;
	}

	return false;
}

bool CCar::SetSpeed(int speed)
{
	if (!m_isEngineOn)
	{
		if (speed == 0)
		{
			m_speed = 0;
			return true;
		}

		return false;
	}

	switch (m_gear)
	{
	case Gear::REVERSE:
		return UpdateSpeedAndDirection(speed, ZERO_SPEED, Direction::Stop) || UpdateSpeedAndDirection(speed, REVERSE_SPEED_NOT_ZERO, Direction::Backward);
	case Gear::NEUTRAL:
		return UpdateSpeedAndDirection(speed, ZERO_SPEED, Direction::Stop);
	case Gear::FIRST:
		return UpdateSpeedAndDirection(speed, ZERO_SPEED, Direction::Stop) || UpdateSpeedAndDirection(speed, FIRST_SPEED_NOT_ZERO, Direction::Forward);
	case Gear::SECOND:
		return UpdateSpeedAndDirection(speed, SECOND_SPEED, Direction::Forward);
	case Gear::THIRD:
		return UpdateSpeedAndDirection(speed, THIRD_SPEED, Direction::Forward);
	case Gear::FOURTH:
		return UpdateSpeedAndDirection(speed, FOURTH_SPEED, Direction::Forward);
	case Gear::FIFTH:
		return UpdateSpeedAndDirection(speed, FIFTH_SPEED, Direction::Forward);
	default:
		return false;
	}
}
