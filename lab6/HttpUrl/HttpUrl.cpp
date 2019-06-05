#include "CHttpUrl.h"
#include <iostream>
#include <fstream>

int main()
{
	std::ifstream fin("input.txt");
	std::ofstream fout("input.txt");
	CHttpUrl url("https://www.my-site-time.com:443/docs/document1.html?page=3450&lang=en#zero17");
	std::cout << url.GetURL() << std::endl;
	std::cout << url.GetProtocol() << std::endl;
	std::cout << url.GetDomain() << std::endl;
	std::cout << url.GetPort() << std::endl;
	std::cout << url.GetDocument() << std::endl;
	CHttpUrl url1("www.my-site-time.com", "docs/document1.html?page=3450&lang=en#zero17", Protocol::HTTP);
	std::cout << url1.GetURL() << std::endl;
	return 0;
}