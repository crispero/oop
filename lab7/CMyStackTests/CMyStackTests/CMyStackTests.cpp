#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "lab7/CMyStack/CMyStack.h"
#include <catch2/catch.hpp>
#include <string>

CMyStack<int> intStack;
CMyStack<std::string> stringStack;

TEST_CASE("tests")
{
	SECTION("Check copy constructor")
	{
		CMyStack<std::string> copiedStack;
		copiedStack.Push("Hello");
		copiedStack.Push("World!");

		CMyStack<std::string> newStack(copiedStack);

		CHECK(copiedStack.GetTop() == newStack.GetTop());
		CHECK(copiedStack.GetTop() == newStack.GetTop());
	}
	SECTION("Try to init empty stack")
	{
		CHECK(intStack.IsEmpty() == true);
		CHECK(intStack.GetSize() == 0);

		CHECK(stringStack.IsEmpty() == true);
		CHECK(stringStack.GetSize() == 0);
	}

	SECTION("Try to push element")
	{
		int value = 4;
		intStack.Push(value);
		CHECK(intStack.GetTop() == 4);
		CHECK(intStack.GetSize() == 1);
	}
}