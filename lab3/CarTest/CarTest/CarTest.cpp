#define CATCH_CONFIG_MAIN
#include "lab3/Car/CCar.h"
#include "lab3/Car/CRemoteControl.h"
#include "lab3/Car/UserCommand.h"
#include <catch2/catch.hpp>

TEST_CASE("Car")
{
	SECTION("Init car")
	{
		CCar car;
		CHECK(car.GetDirection() == "Stop");
		CHECK(car.GetEngine() == "Off");
		CHECK(car.GetGear() == "Neutral");
		CHECK(car.GetSpeed() == 0);
	}

	SECTION("TurnOnEngine() must on engine, TurnOffEngine() must off engine")
	{
		CCar car;
		car.TurnOnEngine();
		CHECK(car.GetEngine() == "On");
		car.TurnOffEngine();
		CHECK(car.GetEngine() == "Off");
	}

	SECTION("Can't change gear and speed when engine off")
	{
		CCar car;
		car.TurnOffEngine();
		CHECK(car.SetGear(-1) == false);
		CHECK(car.SetGear(1) == false);
		CHECK(car.SetGear(2) == false);
		CHECK(car.SetGear(3) == false);
		CHECK(car.SetGear(4) == false);
		CHECK(car.SetGear(5) == false);
		CHECK(car.SetSpeed(5) == false);
		CHECK(car.SetSpeed(10) == false);
		CHECK(car.SetSpeed(50) == false);
	}

	SECTION("Can switch to reverse gear only at zerp speed")
	{
		CCar car;
		car.TurnOnEngine();
		CHECK(car.SetGear(1) == true);
		CHECK(car.SetSpeed(20) == true);
		CHECK(car.SetGear(-1) == false);
		CHECK(car.SetSpeed(0) == true);
		CHECK(car.SetGear(-1) == true);
	}

	SECTION("From the reverse, can switch to the first only at zero speed")
	{
		CCar car;
		car.TurnOnEngine();
		CHECK(car.SetGear(-1) == true);
		CHECK(car.SetSpeed(10) == true);
		CHECK(car.SetGear(1) == false);
		CHECK(car.SetSpeed(0) == true);
		CHECK(car.SetGear(1) == true);
	}

	SECTION("Switching in the reverse direction to a neural transmission at a non-zero speed, you can switch to the first one only after stopping")
	{
		CCar car;
		car.TurnOnEngine();
		CHECK(car.SetGear(-1) == true);
		CHECK(car.SetSpeed(10) == true);
		CHECK(car.GetDirection() == "Backward");
		CHECK(car.SetGear(0) == true);
		CHECK(car.SetGear(1) == false);
		CHECK(car.GetDirection() == "Backward");
		CHECK(car.SetSpeed(0) == true);
		CHECK(car.GetDirection() == "Stop");
		CHECK(car.SetGear(1) == true);
	}

	SECTION("The car's engine can only be turned off at zero speed in neutral")
	{
		CCar car;
		car.TurnOnEngine();
		CHECK(car.SetGear(1) == true);
		CHECK(car.TurnOffEngine() == false);
		CHECK(car.SetSpeed(20) == true);
		CHECK(car.TurnOffEngine() == false);
		CHECK(car.SetSpeed(0) == true);
		CHECK(car.SetGear(-1) == true);
		CHECK(car.SetSpeed(20) == true);
		CHECK(car.TurnOffEngine() == false);
		CHECK(car.SetSpeed(0) == true);
		CHECK(car.TurnOffEngine() == false);
		CHECK(car.SetGear(0) == true);
		CHECK(car.TurnOffEngine() == true);
	}

	SECTION("With the engine off, can only shift to neutral")
	{
		CCar car;
		CHECK(car.GetEngine() == "Off");
		CHECK(car.SetGear(0) == true);
		CHECK(car.SetGear(1) == false);
		CHECK(car.SetGear(2) == false);
		CHECK(car.SetGear(3) == false);
		CHECK(car.SetGear(4) == false);
		CHECK(car.SetGear(5) == false);
		CHECK(car.SetGear(-1) == false);

		car.TurnOnEngine();
		CHECK(car.GetEngine() == "On");
		CHECK(car.GetGear() == "Neutral");
		CHECK(car.GetDirection() == "Stop");
	}

	SECTION("Check speed range and gear")
	{
		CCar car;
		car.TurnOnEngine();

		CHECK(car.SetGear(1) == true);
		CHECK(car.SetSpeed(31) == false);
		CHECK(car.SetSpeed(-10) == false);
		CHECK(car.SetSpeed(20) == true);

		CHECK(car.SetGear(2) == true);
		CHECK(car.SetSpeed(19) == false);
		CHECK(car.SetSpeed(51) == false);
		CHECK(car.SetSpeed(49) == true);

		CHECK(car.SetGear(4) == true);
		CHECK(car.SetGear(5) == false);

		CHECK(car.SetGear(3) == true);
		CHECK(car.SetSpeed(19) == false);
		CHECK(car.SetSpeed(61) == false);
		CHECK(car.SetSpeed(60) == true);

		CHECK(car.SetGear(4) == true);
		CHECK(car.SetSpeed(39) == false);
		CHECK(car.SetSpeed(91) == false);
		CHECK(car.SetSpeed(90) == true);

		CHECK(car.SetGear(5) == true);
		CHECK(car.SetSpeed(49) == false);
		CHECK(car.SetSpeed(151) == false);
		CHECK(car.SetSpeed(150) == true);
	}
}

TEST_CASE("RemoteControl")
{
	SECTION("Standard info")
	{
		CCar car;
		UserCommand userCommand;
		std::stringstream in(userCommand.Info);
		std::stringstream out;

		CRemoteControl remoteControl(car, in, out);

		remoteControl.HandleCommand();
		CHECK(out.str() == "Engine condition: Off\nDirection of travel: Stop\nSpeed: 0\nGear: Neutral\n\n");
	}

	SECTION("Some changes and Info")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		car.SetSpeed(20);
		UserCommand userCommand;
		std::stringstream in(userCommand.Info);
		std::stringstream out;

		CRemoteControl remoteControl(car, in, out);

		remoteControl.HandleCommand();
		CHECK(out.str() == "Engine condition: On\nDirection of travel: Forward\nSpeed: 20\nGear: First\n\n");
	}

	SECTION("EngineOn")
	{
		CCar car;
		UserCommand userCommand;
		std::stringstream in(userCommand.EngineOn);
		std::stringstream out;

		CRemoteControl remoteControl(car, in, out);

		remoteControl.HandleCommand();
		CHECK(out.str() == "Engine on\n");
	}

	SECTION("EngineOn")
	{
		CCar car;
		car.TurnOnEngine();
		UserCommand userCommand;
		std::stringstream in(userCommand.EngineOff);
		std::stringstream out;

		CRemoteControl remoteControl(car, in, out);

		remoteControl.HandleCommand();
		CHECK(out.str() == "Engine off\n");
	}

	SECTION("SetGear not number")
	{
		CCar car;
		std::stringstream in("SetGear error");
		std::stringstream out;

		CRemoteControl remoteControl(car, in, out);

		remoteControl.HandleCommand();
		CHECK(out.str() == "Gear must be a number\nCan't change that gear\n\n");
	}

	SECTION("SetGear works")
	{
		CCar car;
		car.TurnOnEngine();
		std::stringstream in("SetGear 1");
		std::stringstream out;

		CRemoteControl remoteControl(car, in, out);

		remoteControl.HandleCommand();
		CHECK(out.str() == "Gear was changed on: 1\n\n");
	}

	SECTION("SetGear didn't works")
	{
		CCar car;
		car.TurnOnEngine();
		std::stringstream in("SetGear 2");
		std::stringstream out;

		CRemoteControl remoteControl(car, in, out);

		remoteControl.HandleCommand();
		CHECK(out.str() == "Can't change that gear\n\n");
	}

	SECTION("SetSpeed not number")
	{
		CCar car;
		std::stringstream in("SetSpeed error");
		std::stringstream out;

		CRemoteControl remoteControl(car, in, out);

		remoteControl.HandleCommand();
		CHECK(out.str() == "Speed must be a number\nCan't change that speed\n\n");
	}

	SECTION("SetSpeed not number")
	{
		CCar car;
		std::stringstream in("SetSpeed error");
		std::stringstream out;

		CRemoteControl remoteControl(car, in, out);

		remoteControl.HandleCommand();
		CHECK(out.str() == "Speed must be a number\nCan't change that speed\n\n");
	}

	SECTION("SetSpeed didn't work")
	{
		CCar car;
		car.TurnOnEngine();
		std::stringstream in("SetSpeed -1");
		std::stringstream out;

		CRemoteControl remoteControl(car, in, out);

		remoteControl.HandleCommand();
		CHECK(out.str() == "Can't change that speed\n\n");
	}

	SECTION("SetSpeed work")
	{
		CCar car;
		car.TurnOnEngine();
		car.SetGear(1);
		std::stringstream in("SetSpeed 10");
		std::stringstream out;

		CRemoteControl remoteControl(car, in, out);

		remoteControl.HandleCommand();
		CHECK(out.str() == "Speed was changed on: 10\n\n");
	}

	SECTION("Unknown command")
	{
		CCar car;
		std::stringstream in("SetGeer");
		std::stringstream out;

		CRemoteControl remoteControl(car, in, out);

		remoteControl.HandleCommand();
		CHECK(out.str() == "Unknown command!\n");
	}
}