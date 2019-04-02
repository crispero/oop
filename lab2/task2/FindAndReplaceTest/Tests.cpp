#include "pch.h"
#include "..\FindAndReplace\FindAndReplace.h"

TEST_CASE("Standard test")
{
	std::string subject = "Hello, name!";
	std::string search = "name";
	std::string replace = "world";
	std::string result = "Hello, world!";
	CHECK(FindAndReplace(subject, search, replace) == result);
}

TEST_CASE("Only numbers")
{
	std::string subject = "122 132 125";
	std::string search = "12";
	std::string replace = "3";
	std::string result = "32 132 35";
	CHECK(FindAndReplace(subject, search, replace) == result);
}

TEST_CASE("Only numbers without spaces")
{
	std::string subject = "121212";
	std::string search = "12";
	std::string replace = "3";
	std::string result = "333";
	CHECK(FindAndReplace(subject, search, replace) == result);
}

TEST_CASE("Many words replaced")
{
	std::string subject = "hello HellO hel1lo HELLO hello123";
	std::string search = "hello";
	std::string replace = "bye";
	std::string result = "bye HellO hel1lo HELLO bye123";
	CHECK(FindAndReplace(subject, search, replace) == result);
}

