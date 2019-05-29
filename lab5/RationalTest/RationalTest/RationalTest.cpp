#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "lab5/Rational/CRational.h"
#include <catch2/catch.hpp>

TEST_CASE("")
{
	SECTION("Check init")
	{
		CRational rational1(3, 5);
		CHECK(rational1.GetNumerator() == 3);
		CHECK(rational1.GetDenominator() == 5);

		CRational rational2(0, 1);
		CHECK(rational2.GetNumerator() == 0);
		CHECK(rational2.GetDenominator() == 1);

		CHECK_THROWS_AS(CRational(3, 0), std::invalid_argument);

		CRational rational4(-1, 2);
		CHECK(rational4.GetNumerator() == -1);
		CHECK(rational4.GetDenominator() == 2);

		CRational rational5(1, -2);
		CHECK(rational5.GetNumerator() == -1);
		CHECK(rational5.GetDenominator() == 2);

		CRational rational6(-1, -2);
		CHECK(rational6.GetNumerator() == 1);
		CHECK(rational6.GetDenominator() == 2);

		CRational rational7(5, 3);
		CHECK(rational7.GetNumerator() == 5);
		CHECK(rational7.GetDenominator() == 3);

		CRational rational8(6, 3);
		CHECK(rational8.GetNumerator() == 2);
		CHECK(rational8.GetDenominator() == 1);

		CRational rational9(34, 68);
		CHECK(rational9.GetNumerator() == 1);
		CHECK(rational9.GetDenominator() == 2);

		CRational rational10(450, 3000);
		CHECK(rational10.GetNumerator() == 3);
		CHECK(rational10.GetDenominator() == 20);
	}

	SECTION("To double")
	{
		CRational rational(1, 2);
		CHECK(rational.ToDouble() == 0.5);

		CRational rational1(3, 5);
		CHECK(rational1.ToDouble() == 0.6);

		CRational rational2(10, 10);
		CHECK(rational2.ToDouble() == 1);

		CRational rational3(21, 3);
		CHECK(rational3.ToDouble() == 7);
	}

	SECTION("GreatestCommonDenominator")
	{
		CHECK(GreatestCommonDenominator(3, 6) == 3);
		CHECK(GreatestCommonDenominator(3, 2) == 1);
		CHECK(GreatestCommonDenominator(5, 3) == 1);
		CHECK(GreatestCommonDenominator(49, 7) == 7);
		CHECK(GreatestCommonDenominator(22, 11) == 11);
		CHECK(GreatestCommonDenominator(50, 5) == 5);
		CHECK(GreatestCommonDenominator(0.2, 5) == 5);
		CHECK(GreatestCommonDenominator(5.2, 5) == 5);
		CHECK(GreatestCommonDenominator(5.2, 6) == 1);
		CHECK(GreatestCommonDenominator(4.4, 2.2) == 2);
		CHECK(GreatestCommonDenominator(-1, 2) == 1);
		CHECK(GreatestCommonDenominator(1, -2) == 1);
	}
}

TEST_CASE("operators")
{
	SECTION("unary + ")
	{
		CRational rational(1, 2);
		CRational rationalResult = +rational;
		CHECK(rationalResult.GetNumerator() == 1);
		CHECK(rationalResult.GetDenominator() == 2);

		CRational rational1(46, 41);
		CRational rationalResult1 = +rational1;
		CHECK(rationalResult1.GetNumerator() == 46);
		CHECK(rationalResult1.GetDenominator() == 41);
	}

	SECTION("unary - ")
	{
		CRational rational(1, 2);
		CRational rationalResult = -rational;
		CHECK(rationalResult.GetNumerator() == -1);
		CHECK(rationalResult.GetDenominator() == 2);

		CRational rational1(46, 41);
		CRational rationalResult1 = -rational1;
		CHECK(rationalResult1.GetNumerator() == -46);
		CHECK(rationalResult1.GetDenominator() == 41);

		CRational rational2(-1, 3);
		CRational rationalResult2 = -rational2;
		CHECK(rationalResult2.GetNumerator() == 1);
		CHECK(rationalResult2.GetDenominator() == 3);
	}

	SECTION("binary + ")
	{
		CRational rational1(1, 3);
		CRational rational2(1, 3);
		CRational rationalResult = rational1 + rational2;
		CHECK(rationalResult.GetNumerator() == 2);
		CHECK(rationalResult.GetDenominator() == 3);

		CRational rational3(5, 4);
		CRational rational4(6, 5);
		CRational rationalResult2 = rational3 + rational4;
		CHECK(rationalResult2.GetNumerator() == 49);
		CHECK(rationalResult2.GetDenominator() == 20);

		CRational rational5(-1, 3);
		CRational rational6(6, 4);
		CRational rationalResult3 = rational5 + rational6;
		CHECK(rationalResult3.GetNumerator() == 7);
		CHECK(rationalResult3.GetDenominator() == 6);

		CRational rational5(6, 7);
		CRational rational6(6, 4);
		CRational rationalResult3 = rational5 + rational6;
		CHECK(rationalResult3.GetNumerator() == 7);
		CHECK(rationalResult3.GetDenominator() == 6);
	}

	SECTION("binary - ")
	{

	}
}