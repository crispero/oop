#include "pch.h"
#include "CCar.h"
#include "UserChoice.h"
#include <iostream>

int main()
{
	CCar car;
	std::string str;

	while (true)
	{
		std::cout << ">";
		std::cin >> str;
		if (str == Info)
			car.GetCurrentInfo();
		else if (str == EngineOn)
			car.TurnOnEngine();
		else if (str == EngineOff)
			car.TurnOffEngine();
		else if (str == SetGear)
		{
			int gear;
			std::cin >> gear;
			car.SetGear(gear);
		}
		else if (str == SetSpeed)
		{
			int speed;
			std::cin >> speed;
			car.SetSpeed(speed);
		}
		else
			std::cout << "" << std::endl;
	}
}