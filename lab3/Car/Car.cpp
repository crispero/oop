#include "pch.h"
#include "CCar.h"
#include "CRemoteControl.h"
#include <iostream>

using namespace std;

int main()
{
	CCar car;
	CRemoteControl remoteControl(car, cin, cout);

	while (!std::cin.eof())
	{
		remoteControl.HandleCommand();
	}

	return 0;
}
