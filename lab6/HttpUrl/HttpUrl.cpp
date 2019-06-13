#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <iostream>

int main()
{
	std::string str;
	while (getline(std::cin, str))
	{
		try
		{
			CHttpUrl url(str);
			std::cout << "Protocol: " << url.GetProtocol() << std::endl;
			std::cout << "Domain: " << url.GetDomain() << std::endl;
			std::cout << "Port: " << url.GetPort() << std::endl;
			std::cout << "Document: " << url.GetDocument() << std::endl;
			std::cout << "URL: "  << url.GetURL() << std::endl;
		}
		catch (const CUrlParsingError& err)
		{
			std::cout << err.what() << std::endl;
		}
		std::cout << std::endl;
	}

	return 0;
}