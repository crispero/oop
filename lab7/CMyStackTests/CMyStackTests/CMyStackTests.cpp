#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "lab7/CMyStack/CMyStack.h"
#include <catch2/catch.hpp>
#include <string>

CMyStack<int> intStack;
CMyStack<std::string> stringStack;

TEST_CASE("tests")
{
	SECTION("Try to init default stack")
	{
		CHECK(intStack.IsEmpty() == true);
		CHECK(intStack.GetSize() == 0);
		CHECK_THROWS_AS(intStack.GetTop(), std::logic_error);

		CHECK(stringStack.IsEmpty() == true);
		CHECK(stringStack.GetSize() == 0);
		CHECK_THROWS_AS(stringStack.GetTop(), std::logic_error);
	}

	SECTION("Try to push and pop one element")
	{
		int value = 4;
		intStack.Push(value);
		CHECK(intStack.GetTop() == value);
		CHECK(intStack.GetSize() == 1);
		intStack.Pop();
		CHECK_THROWS_AS(intStack.GetTop(), std::logic_error);
		CHECK(intStack.GetSize() == 0);

		std::string str = "Hello";
		stringStack.Push(str);
		CHECK(stringStack.GetTop() == str);
		CHECK(stringStack.GetSize() == 1);
		stringStack.Pop();
		CHECK_THROWS_AS(stringStack.GetTop(), std::logic_error);
		CHECK(stringStack.GetSize() == 0);
	}

	SECTION("Try to push and pop some element")
	{
		intStack.Push(1);
		intStack.Push(2);
		intStack.Push(3);

		CHECK(intStack.IsEmpty() == false);

		CHECK(intStack.GetTop() == 3);
		CHECK(intStack.GetSize() == 3);
		intStack.Pop();

		CHECK(intStack.GetTop() == 2);
		CHECK(intStack.GetSize() == 2);
		intStack.Pop();

		CHECK(intStack.GetTop() == 1);
		CHECK(intStack.GetSize() == 1);
		intStack.Pop();

		CHECK(intStack.IsEmpty() == true);

		stringStack.Push("Hello");
		stringStack.Push("World");
		stringStack.Push("!");

		CHECK(stringStack.IsEmpty() == false);

		CHECK(stringStack.GetTop() == "!");
		CHECK(stringStack.GetSize() == 3);
		stringStack.Pop();

		CHECK(stringStack.GetTop() == "World");
		CHECK(stringStack.GetSize() == 2);
		stringStack.Pop();

		CHECK(stringStack.GetTop() == "Hello");
		CHECK(stringStack.GetSize() == 1);
		stringStack.Pop();

		CHECK(stringStack.IsEmpty() == true);
	}

	SECTION("Try to clear stack")
	{
		intStack.Push(1);
		intStack.Push(2);
		intStack.Push(3);

		CHECK(intStack.IsEmpty() == false);
		intStack.Clear();
		CHECK(intStack.IsEmpty() == true);

		stringStack.Push("Hello");
		stringStack.Push("World");
		stringStack.Push("!");

		CHECK(stringStack.IsEmpty() == false);
		stringStack.Clear();
		CHECK(stringStack.IsEmpty() == true);
	}

	SECTION("Check copy constructor")
	{
		CMyStack<int> copiedIntStack;
		copiedIntStack.Push(1);
		copiedIntStack.Push(2);

		CMyStack<int> newIntStack(copiedIntStack);

		CHECK(copiedIntStack.GetTop() == newIntStack.GetTop());
		CHECK(copiedIntStack.IsEmpty() == false);
		CHECK(copiedIntStack.GetSize() == 2);

		CMyStack<std::string> copiedStrStack;
		copiedStrStack.Push("Hello");
		copiedStrStack.Push("World!");

		CMyStack<std::string> newStrStack(copiedStrStack);

		CHECK(copiedStrStack.GetTop() == newStrStack.GetTop());
		CHECK(copiedStrStack.IsEmpty() == false);
		CHECK(copiedStrStack.GetSize() == 2);
	}

	SECTION("Check copy empty constructor")
	{
		CMyStack<int> copyIntStack(intStack);

		CHECK(copyIntStack.IsEmpty() == true);
		CHECK(copyIntStack.IsEmpty() == true);

		CHECK_THROWS_AS(intStack.GetTop(), std::logic_error);
		CHECK_THROWS_AS(copyIntStack.GetTop(), std::logic_error);

		CMyStack<std::string> copyStrStack(stringStack);

		CHECK(copyStrStack.IsEmpty() == true);
		CHECK(copyStrStack.IsEmpty() == true);

		CHECK_THROWS_AS(stringStack.GetTop(), std::logic_error);
		CHECK_THROWS_AS(copyStrStack.GetTop(), std::logic_error);
	}

	SECTION("Check copy stack operator=")
	{
		intStack.Push(1);
		intStack.Push(2);
		CMyStack<int> copyIntStack;
		copyIntStack.Push(3);
		copyIntStack.Push(4);
		copyIntStack.Push(5);

		CHECK(intStack.GetTop() != copyIntStack.GetTop());
		CHECK(intStack.GetSize() != copyIntStack.GetSize());

		copyIntStack = intStack;

		CHECK(intStack.GetTop() == copyIntStack.GetTop());
		CHECK(intStack.GetSize() == copyIntStack.GetSize());
		copyIntStack.Pop();
		CHECK(intStack.GetTop() != copyIntStack.GetTop());
		CHECK(copyIntStack.GetTop() == 1);
		CHECK(intStack.GetSize() != copyIntStack.GetSize());

		stringStack.Push("Hello");
		stringStack.Push("World");
		CMyStack<std::string> copyStrStack;
		copyStrStack.Push("Taigin");
		copyStrStack.Push("Igor");
		copyStrStack.Push("Alexandrovich");

		CHECK(stringStack.GetTop() != copyStrStack.GetTop());
		CHECK(stringStack.GetSize() != copyStrStack.GetSize());

		copyStrStack = stringStack;

		CHECK(stringStack.GetTop() == copyStrStack.GetTop());
		CHECK(stringStack.GetSize() == copyStrStack.GetSize());
		copyStrStack.Pop();
		CHECK(stringStack.GetTop() != copyStrStack.GetTop());
		CHECK(copyStrStack.GetTop() == "Hello");
		CHECK(stringStack.GetSize() != copyStrStack.GetSize());
	}

	SECTION("Check copy empty stack operator=")
	{
		CMyStack<int> copyIntStack;
		intStack = copyIntStack;

		CHECK(intStack.IsEmpty() == true);
		CHECK(intStack.GetSize() == 0);
		CHECK_THROWS_AS(intStack.GetTop(), std::logic_error);

		CMyStack<std::string> copyStrStack;
		stringStack = copyStrStack;

		CHECK(stringStack.IsEmpty() == true);
		CHECK(stringStack.GetSize() == 0);
		CHECK_THROWS_AS(stringStack.GetTop(), std::logic_error);
	}

	SECTION("Self-assignment copy stack operator=")
	{
		intStack.Push(1);
		intStack.Push(2);

		intStack = intStack;
		CHECK(intStack.GetTop() == 2);
		intStack.Clear();

		stringStack.Push("Hello");
		stringStack.Push("World");

		stringStack = stringStack;
		CHECK(stringStack.GetTop() == "World");
		stringStack.Clear();
	}

	SECTION("Check move constructor")
	{
		intStack.Push(1);
		intStack.Push(2);

		CMyStack<int> moveIntStack(std::move(intStack));

		CHECK(intStack.IsEmpty() == true);
		CHECK(moveIntStack.IsEmpty() == false);
		CHECK_THROWS_AS(intStack.GetTop(), std::logic_error);
		CHECK(moveIntStack.GetTop() == 2);

		stringStack.Push("Hello");
		stringStack.Push("world");

		CMyStack<std::string> moveStrStack(std::move(stringStack));

		CHECK(stringStack.IsEmpty() == true);
		CHECK(moveStrStack.IsEmpty() == false);
		CHECK_THROWS_AS(stringStack.GetTop(), std::logic_error);
		CHECK(moveStrStack.GetTop() == "world");
	}

	SECTION("Check move empty constructor")
	{
		CMyStack<int> moveIntStack(std::move(intStack));

		CHECK(intStack.IsEmpty() == true);
		CHECK(moveIntStack.IsEmpty() == true);
		CHECK_THROWS_AS(intStack.GetTop(), std::logic_error);
		CHECK_THROWS_AS(moveIntStack.GetTop(), std::logic_error);

		CMyStack<std::string> moveStrStack(std::move(stringStack));

		CHECK(stringStack.IsEmpty() == true);
		CHECK(moveStrStack.IsEmpty() == true);
		CHECK_THROWS_AS(stringStack.GetTop(), std::logic_error);
		CHECK_THROWS_AS(moveStrStack.GetTop(), std::logic_error);
	}

	SECTION("Check move stack operator=")
	{
		intStack.Push(5);
		CMyStack<int> moveIntStack;
		moveIntStack.Push(1);
		moveIntStack.Push(2);
		moveIntStack.Push(3);
		moveIntStack.Push(4);

		intStack = std::move(moveIntStack);

		CHECK(intStack.GetTop() == 4);
		CHECK_THROWS_AS(moveIntStack.GetTop(), std::logic_error);
		CHECK(moveIntStack.IsEmpty() == true);
		intStack.Clear();

		stringStack.Push("Hello");
		CMyStack<std::string> moveStrStack;
		moveStrStack.Push("life");
		moveStrStack.Push("is");
		moveStrStack.Push("very");
		moveStrStack.Push("good");

		stringStack = std::move(moveStrStack);

		CHECK(stringStack.GetTop() == "good");
		CHECK_THROWS_AS(moveStrStack.GetTop(), std::logic_error);
		CHECK(moveStrStack.IsEmpty() == true);
		stringStack.Clear();
	}

	SECTION("Check move empty stack operator=")
	{
		CMyStack<int> moveIntStack;
		intStack = std::move(moveIntStack);

		CHECK(intStack.IsEmpty() == true);
		CHECK(moveIntStack.IsEmpty() == true);
		CHECK_THROWS_AS(intStack.GetTop(), std::logic_error);
		CHECK_THROWS_AS(moveIntStack.GetTop(), std::logic_error);

		CMyStack<std::string> moveStrStack;
		stringStack = std::move(moveStrStack);

		CHECK(stringStack.IsEmpty() == true);
		CHECK(moveStrStack.IsEmpty() == true);
		CHECK_THROWS_AS(stringStack.GetTop(), std::logic_error);
		CHECK_THROWS_AS(moveStrStack.GetTop(), std::logic_error);
	}

	SECTION("Self-assignment move stack operator=")
	{
		intStack.Push(1);
		intStack.Push(2);

		intStack = std::move(intStack);

		CHECK(intStack.IsEmpty() == false);
		CHECK(intStack.GetTop() == 2);

		stringStack.Push("Hello");
		stringStack.Push("world");

		stringStack = std::move(stringStack);

		CHECK(stringStack.IsEmpty() == false);
		CHECK(stringStack.GetTop() == "world");
	}
}