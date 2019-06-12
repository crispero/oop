#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "Sportsman.h"
#include "lab7/FindMaxEx/FindMaxEx.h"
#include <catch2/catch.hpp>

const Sportsman sportsman1 = { "Foster Michael", 180, 65.3f };
const Sportsman sportsman2 = { "Watson Edward", 165, 80.5f };
const Sportsman sportsman3 = { "Jordan David", 176, 92.1f };

const std::vector<Sportsman> sportsmans = { sportsman1, sportsman2, sportsman3 };
Sportsman sportsman;

TEST_CASE("FindMaxEx")
{
	SECTION("empty vector")
	{
		std::vector<Sportsman> emptyVector;
		CHECK(emptyVector.empty());
		CHECK(!FindMax(emptyVector, sportsman, IsLessName));
		CHECK(!FindMax(emptyVector, sportsman, IsLessHeight));
		CHECK(!FindMax(emptyVector, sportsman, IsLessWeight));
	}

	SECTION("by name")
	{
		std::string maxName = sportsman2.name;
		CHECK(FindMax(sportsmans, sportsman, IsLessName));
		CHECK(sportsman.name == maxName);
	}

	SECTION("by height")
	{
		int maxHeight = sportsman1.height;
		CHECK(FindMax(sportsmans, sportsman, IsLessHeight));
		CHECK(sportsman.height == maxHeight);
	}

	SECTION("by weight")
	{
		float maxWeight = sportsman3.weight;
		CHECK(FindMax(sportsmans, sportsman, IsLessWeight));
		CHECK(sportsman.weight == maxWeight);
	}
}