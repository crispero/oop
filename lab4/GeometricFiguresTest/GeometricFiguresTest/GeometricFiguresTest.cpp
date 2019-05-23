#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("2 + 2 must return 4")
{
	REQUIRE(2 + 2 == 4);
}