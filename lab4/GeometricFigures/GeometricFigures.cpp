#include "CRemoteControl.h"
#include "Const.h"
#include <fstream>

int main(int argc, char* argv[])
{
	int parametersNumber = argc;

	if (parametersNumber != 2)
	{
		std::cout << ERROR_INVALID_ARGUMENTS << std::endl;
		return 1;
	}

	std::string fileName = argv[1];

	std::ifstream fin(fileName);

	if (!fin.is_open())
	{
		std::cout << ERROR_FAILED_OPEN_FILE << std::endl;
		return 1;
	}

	CRemoteControl remoteControl(fin, std::cout);
	remoteControl.HandleCommand();
	remoteControl.PrintInfo();

	return 0;
}
